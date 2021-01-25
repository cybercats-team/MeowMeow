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

typedef struct SpriteSize {
  unsigned int width = 0;
  unsigned int height = 0;
} SpriteSize;

typedef struct SpriteRect: SpriteSize {
  unsigned int left = 0;
  unsigned int top = 0;
} SpriteRect;

typedef struct SpriteFrame {
  SpriteRect rect{};
  SpriteRect rect2x{};
  SpriteRect rect4x{};
} SpriteFrame;

typedef struct SpriteSetInfo {
  char path[RESOURCE_MAX_PATH] = "";
  char path2x[RESOURCE_MAX_PATH] = "";
  char path4x[RESOURCE_MAX_PATH] = "";
  SpriteSize spriteSize{};
  SpriteSize spriteSize2x{};
  SpriteSize spriteSize4x{};
} SpriteSetInfo;

typedef struct SpriteInfo {
  bool animated = false;
  unsigned int animationDuration = 0;
  unsigned int framesCount = 1;
  SpriteFrame frame{};
} SpriteInfo;

class SpriteManager {
  
  private:
    static const std::map<ObjectType, std::string> bundlesPath;
    
    ResourceManager& resourceManager;
    std::map<ObjectType, std::vector<std::string>> spriteSetsPaths;
    
    bool openBundle(std::ifstream &file, const std::string& path, BundleHeader& header);
  public:
    explicit SpriteManager(ResourceManager& resourceManager);
    bool initialize();
};

#endif /* TextureManager_hpp */
