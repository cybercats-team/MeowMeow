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

#include "../interfaces/UIManager.h"
#include "../primitives/SpriteSet.h"
#include "../utils/Debug.h"


using SpriteSetInfo = struct SpriteSetInfo {
  char path[RESOURCE_MAX_PATH] = "";
  char path2k[RESOURCE_MAX_PATH] = "";
  char path4k[RESOURCE_MAX_PATH] = "";
  Dimensions spriteSize{};
  Dimensions spriteSize2k{};
  Dimensions spriteSize4k{};
};

using TextureItem = struct TextureItem {
  char infoPath[RESOURCE_MAX_PATH] = "";
};

class SpriteManager: public UIManager {
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
