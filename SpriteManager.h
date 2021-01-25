//
//  SpriteManager.hpp
//  MeowMeow
//
//  Created by Alex Serdukov on 23.01.2021.
//  Copyright © 2021 Alex Serdukov. All rights reserved.
//

#ifndef TextureManager_hpp
#define TextureManager_hpp

#include <fstream>
#include <cstring>

#include "ResourceManager.h"
#include "SpriteSet.h"
#include "Object.h"
#include "Debug.h"

#define TEXTURE_BUNDLE_MAGIC "BUNDLE"

enum class BundleType {
  TexturesList,
  TextureInfo
};

typedef struct BundleHeader {
  char magic[7] = TEXTURE_BUNDLE_MAGIC;
  BundleType bundleType = BundleType::TexturesList;
  ObjectType objectType = ObjectType::Terrain;
  unsigned int itemsCount = 0;
} BundleHeader;

typedef struct TextureInfo {
  char infoPath[RESOURCE_MAX_PATH] = "";
} TextureItem;

class SpriteManager {
  private:
    const std::map<ObjectType, std::string> bundlesPath = {
      {ObjectType::Terrain, "terrain"},
      {ObjectType::MobileObject, "mobileObjects"}
    };
    
    ResourceManager& resourceManager;
    std::map<ObjectType, std::vector<std::string>> spriteSetsPaths;
    
    bool openBundle(std::ifstream &file, const std::string& path, BundleHeader& header);
  public:
    explicit SpriteManager(ResourceManager& resourceManager);
    bool initialize();
    bool load(SpriteSet& spriteSet, ObjectType objectType, unsigned int index);
};

#endif /* TextureManager_hpp */
