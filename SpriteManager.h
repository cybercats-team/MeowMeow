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

#include "BundleManager.h"
#include "SpriteSet.h"
#include "TypeDefs.h"
#include "Debug.h"

class SpriteManager: public BundleManager {
  private:
    const std::map<ObjectType, std::string> bundlesPath = {
      {ObjectType::Terrain, "terrain"},
      {ObjectType::MobileObject, "mobileObjects"}
    };    
    
    std::map<ObjectType, std::vector<std::string>> spriteSetsPaths = {
      {ObjectType::Terrain, {}},
      {ObjectType::MobileObject, {}}
    };
    
    Dimensions getSpriteSize(SpriteSetInfo &info) const;
    Rectangle getSpriteRect(SpriteFrame &frame) const;
    std::string getTexturePath(SpriteSetInfo &info) const;
  public:
    SpriteManager(ResourceManager& resourceManager, Screen& screen);
    bool initialize();
    bool load(SpriteSet& spriteSet, ObjectType objectType, unsigned int index);
};

#endif /* TextureManager_hpp */
