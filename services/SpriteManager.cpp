//
//  SpriteManager.cpp
//  MeowMeow
//
//  Created by Alex Serdukov on 23.01.2021.
//  Copyright © 2021 Alex Serdukov. All rights reserved.
//

#include "SpriteManager.h"

SpriteManager::SpriteManager(ResourceManager& resourceManager, Screen& screen) :
  UIManager(resourceManager, screen) {}

bool SpriteManager::initialize() {
  using namespace std;

  for (auto& [objectType, path]: bundlesPath) {
    ifstream listFile;
    BundleHeader header {};
    TextureItem textureItem {};

    Debug::printf("Loading bundle %s", path);
    
    if (!resourceManager.load(listFile, header, path)) {
      return false;
    }
    
    for (unsigned int textureId = 0; textureId < header.itemsCount; textureId++) {
      listFile.read((char *) &textureItem, sizeof(textureItem));
      
      string texturePath(textureItem.infoPath);
      spriteSetsPaths[objectType].push_back(texturePath);
      Debug::printf("Added texture ref %s", texturePath);
    }
    
    listFile.close();    
  }
  
  return true;
}

bool SpriteManager::load(SpriteSet &spriteSet, ObjectType objectType, unsigned int index) {
  using namespace std;

  Debug::printf("Loading %s sprite set #%d",
    (objectType == ObjectType::Terrain ? "terrain" : "mobile object"), 
    index
  );

  vector<string>& paths = spriteSetsPaths[objectType];

  if (index > paths.size()) {
    Debug::printf("SpriteObject set #%d not exists", index);
    return false;
  }

  ifstream spriteFile;
  BundleHeader header {};
  string& path = paths[index];

  Debug::printf("Loading bundle %s", path);

  if (!resourceManager.load(spriteFile, header, path)) {
    return false;
  }

  SpriteSetInfo info{};
  spriteFile.read((char *) &info, sizeof(info));

  unsigned int spritesCount = header.itemsCount;
  string texturePath = getTexturePath(info);

  spriteSet.spritesCount = spritesCount;
  spriteSet.spriteSize = getSpriteSize(info);

  for (unsigned int spriteIndex = 0; spriteIndex < spritesCount; spriteIndex++) {
    SpriteInfo spriteInfo{};
    vector<Rectangle> frames{};

    spriteFile.read((char *) &spriteInfo, sizeof(spriteInfo));
    spriteSet.sprites.push_back(spriteInfo);

    unsigned int framesCount = spriteInfo.animated ? spriteInfo.framesCount : 1;

    for (unsigned int frameIndex = 0; frameIndex < framesCount; frameIndex++) {
      SpriteFrame frame{};
      
      spriteFile.read((char *) &frame, sizeof(frame));      
      frames.push_back(getSpriteRect(frame));
    }

    spriteSet.frames.push_back(frames);
  }

  spriteFile.close();

  Debug::printf("Loading texture %s", texturePath);

  return resourceManager.load(spriteSet.texture, texturePath);
}

Dimensions SpriteManager::getSpriteSize(SpriteSetInfo &info) const {
  return screenQuery(info.spriteSize, info.spriteSize2k, info.spriteSize4k);
}

Rectangle SpriteManager::getSpriteRect(SpriteFrame &frame) const {
  return screenQuery(frame.rect, frame.rect2k, frame.rect4k);
}

std::string SpriteManager::getTexturePath(SpriteSetInfo &info) const {
  char* path = screenQuery(info.path, info.path2k, info.path4k);

  return std::string(path);
}
