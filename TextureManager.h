//
//  TextureManager.hpp
//  MeowMeow
//
//  Created by Alex Serdukov on 23.01.2021.
//  Copyright © 2021 Alex Serdukov. All rights reserved.
//

#ifndef TextureManager_hpp
#define TextureManager_hpp

#include "ResourceManager.h"
#include "Object.h"

#define TEXTURE_BUNDLE_MAGIC "BUNDLE"

using namespace std;

enum class BundleType {
  TexturesList,
  TextureInfo
};

typedef struct {
  char magic[7] = TEXTURE_BUNDLE_MAGIC;
  BundleType bundleType;
  ObjectType objectType;
  unsigned int itemsCount;
} TextureBundleHeader;

typedef struct {
  char infoPath[RESOURCE_MAX_PATH];
} TextureItem;

typedef struct {
  unsigned int width;
  unsigned int height;
} SpriteSize;

typedef struct {
  unsigned int left;
  unsigned int top;
  struct SpriteSize;
} SpriteRect;

typedef struct {
  SpriteRect rect;
  SpriteRect rect2x;
  SpriteRect rect4x;
} SpriteFrame;

typedef struct {
  char path[RESOURCE_MAX_PATH];
  char path2x[RESOURCE_MAX_PATH];
  char path4x[RESOURCE_MAX_PATH];
  SpriteSize spriteSize;
  SpriteSize spriteSize2x;
  SpriteSize spriteSize4x;
} TextureInfo;

typedef struct {
  bool animated = false;
  unsigned int animationDuration = 0;
  unsigned int framesCount;
  SpriteFrame frame;
} SpriteInfo;

class TextureManager {
  
  private:
    ResourceManager& resourceManager;
  
    map<ObjectType, string> textureBundles = {
      {ObjectType::Terrain, "terrains"},
      {ObjectType::MobileObject, "mobileObjects"}
    };
  
  public:
    TextureManager(ResourceManager& resourceManager);
};

#endif /* TextureManager_hpp */
