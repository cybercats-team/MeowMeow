//
//  SpriteManager.cpp
//  MeowMeow
//
//  Created by Alex Serdukov on 23.01.2021.
//  Copyright © 2021 Alex Serdukov. All rights reserved.
//

#include "SpriteManager.h"

SpriteManager::SpriteManager(ResourceManager& resourceManager, Screen& screen) :
  screen(screen),
  resourceManager(resourceManager) {}

bool SpriteManager::initialize() {
  using namespace std;

  for (auto& [objectType, path]: bundlesPath) {
    ifstream listFile;
    BundleHeader header {};
    TextureInfo textureItem {};

    debugPrint("Loading bundle " + path);
    
    if (!openBundle(listFile, path, header)) {
      return false;
    }
    
    for (unsigned int textureId = 0; textureId < header.itemsCount; textureId++) {
      listFile.read((char *) &textureItem, sizeof(textureItem));
      
      string texturePath(textureItem.infoPath);
      spriteSetsPaths[objectType].push_back(texturePath);
      debugPrint("Added texture ref " + texturePath);
    }
    
    listFile.close();    
  }
  
  return true;
}

bool SpriteManager::openBundle(std::ifstream &file, const std::string& path, BundleHeader& header) {
  if (!resourceManager.load(file, path, ResourceType::TextureBundle)) {
    debugPrint("Failed to open bundle file");
    return false;
  }
  
  file.read((char *) &header, sizeof(header));
  
  if (strcmp(header.magic, TEXTURE_BUNDLE_MAGIC) != 0) {
    debugPrint("Bundle signature not match");
    file.close();
    return false;
  }
  
  return true;
}

bool SpriteManager::load(SpriteSet &spriteSet, ObjectType objectType, unsigned int index) {
  using namespace std;

  debugPrint("Loading " +
    (string) (objectType == ObjectType::Terrain ? "terrain" : "mobile object") +
    " sprite set #" +
    to_string(index)
  );

  vector<string>& paths = spriteSetsPaths[objectType];

  if (index > paths.size()) {
    debugPrint("Sprite set #" + to_string(index) + "not exists");
    return false;
  }

  ifstream spriteFile;
  BundleHeader header {};
  string& path = paths[index];

  debugPrint("Loading bundle " + path);

  if (!openBundle(spriteFile, path, header)) {
    return false;
  }

  unsigned int spritesCount = header.itemsCount;

  spriteSet.scale = screen.scale;
  spriteSet.spritesCount = spritesCount;
  spriteFile.read((char *) &spriteSet.info, sizeof(spriteSet.info));

  for (unsigned int spriteIndex = 0; spriteIndex < spritesCount; spriteIndex++) {
    SpriteInfo spriteInfo{};

    spriteFile.read((char *) &spriteInfo, sizeof(spriteInfo));
    spriteSet.sprites.push_back(spriteInfo);

    if (!spriteInfo.animated) {
      continue;
    }

    unsigned int framesCount = spriteInfo.framesCount;
    vector<SpriteFrame> frames{};

    for (unsigned int frameIndex = 0; frameIndex < framesCount; frameIndex++) {
      SpriteFrame frame{};

      spriteFile.read((char *) &frame, sizeof(frame));
      frames.push_back(frame);
    }

    spriteSet.frames.push_back(frames);
  }

  spriteFile.close();
  return true;
}
