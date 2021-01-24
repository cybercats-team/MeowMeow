//
//  TextureManager.cpp
//  MeowMeow
//
//  Created by Alex Serdukov on 23.01.2021.
//  Copyright © 2021 Alex Serdukov. All rights reserved.
//

#include "TextureManager.h"

const map<ObjectType, string> TextureManager::textureListsPath = {
  {ObjectType::Terrain, "terrain"},
  {ObjectType::MobileObject, "mobileObjects"}
};

TextureManager::TextureManager(ResourceManager& resourceManager) :
  resourceManager(resourceManager),
  textureBundlesPath({
    {ObjectType::Terrain, {}},
    {ObjectType::MobileObject, {}}
  }) {}

bool TextureManager::initialize() {
  for (auto& [objectType, path]: textureListsPath) {
    ifstream listFile;
    TextureBundleHeader header {};
    TextureItem textureItem {};

    debugPrint("Loading bundle " + path);
    
    if (!openBundle(listFile, path, header)) {
      return false;
    }
    
    for (unsigned int textureId = 0; textureId < header.itemsCount; textureId++) {
      listFile.read((char *) &textureItem, sizeof(textureItem));
      
      string texturePath(textureItem.infoPath);
      textureBundlesPath[objectType].push_back(texturePath);
      debugPrint("Added texture ref " + texturePath);
    }
    
    listFile.close();    
  }
  
  return true;
}

bool TextureManager::openBundle(ifstream &file, const string& path, TextureBundleHeader& header) {
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
