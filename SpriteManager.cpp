//
//  SpriteManager.cpp
//  MeowMeow
//
//  Created by Alex Serdukov on 23.01.2021.
//  Copyright © 2021 Alex Serdukov. All rights reserved.
//

#include "SpriteManager.h"

SpriteManager::SpriteManager(ResourceManager& resourceManager) :
  resourceManager(resourceManager),
  spriteSetsPaths({
    {ObjectType::Terrain, {}},
    {ObjectType::MobileObject, {}}
  }) {}

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
