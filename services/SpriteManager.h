//
//  SpriteManager.hpp
//  MeowMeow
//
//  Created by Alex Serdukov on 23.01.2021.
//  Copyright © 2021 Alex Serdukov. All rights reserved.
//

#ifndef SpriteManager_h
#define SpriteManager_h

#include <fstream>

#include "../interfaces/BundleManager.h"
#include "../primitives/SpriteSet.h"
#include "../interfaces/TypeDefs.h"
#include "../Debug.h"

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
    bool initialize() override;
    bool load(SpriteSet& spriteSet, ObjectType objectType, unsigned int index);
};

#endif /* SpriteManager_h */
