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

const char TextureBundleMagic[7] = "BUNDLE";

enum class TextureBundleType {
  Terrain,
  MobileObject
};

typedef struct {
  char magic[7];
  unsigned int texturesCount;
} TextureBundleHeader;

typedef struct {
  unsigned int spriteSize;
  unsigned int spritesCount;
} TextureHeader;

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
