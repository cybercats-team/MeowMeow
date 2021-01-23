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

using namespace std;

typedef char BundleMagic[3];

const BundleMagic TextureBundleMagic = "BN";
const BundleMagic TextureBundleTextureMagic = "TX";
const BundleMagic TextureBundleSpriteMagic = "SP";

enum class TextureBundleType {
  Terrain,
  MobileObject
};

typedef struct {
  BundleMagic magic;
  unsigned int texturesCount;
} TextureBundleHeader;

typedef struct {
  BundleMagic magic;
  unsigned int spriteSize;
  unsigned int spritesCount;
} TextureBundleTextureHeader;

typedef unsigned int FramesCount;

class TextureManager {
  
  private:
    ResourceManager& resourceManager;
  
    map<TextureBundleType, string> textureBundles = {
      {TextureBundleType::Terrain, "terrains"},
      {TextureBundleType::MobileObject, "mobileObjects"}
    };
  
  public:
    TextureManager(ResourceManager& resourceManager);
};

#endif /* TextureManager_hpp */
