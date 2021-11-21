//
//  LevelManager.hpp
//  MeowMeow
//
//  Created by Alex Serdukov on 16.02.2021.
//  Copyright © 2021 Alex Serdukov. All rights reserved.
//

#ifndef LevelManager_h
#define LevelManager_h

#include <vector>
#include "../utils/Array.h"

#include "../Debug.h"
#include "../interfaces/TypeDefs.h"

#include "../primitives/LevelRealm.h"
#include "../primitives/LevelMap.h"
#include "../primitives/SpriteSet.h"
#include "../primitives/SpriteObject.h"

#include "../interfaces/BundleManager.h"
#include "SpriteManager.h"

class LevelManager: public BundleManager {
  private:
    const std::string bundlePath = "levels";
    SpriteManager& spriteManager;
  
    std::vector<RealmInfo> realms;
    std::vector<std::vector<LevelInfo>> levels;
    std::map<ObjectType, std::map<unsigned int, SpriteSet>> spriteSets = {
      {ObjectType::Terrain, {}},
      {ObjectType::MobileObject, {}}
    };

    void fillLevelNames(std::vector<std::string>& levelNames, unsigned int realmId);
    Dimensions getTileSize(MapInfo &info) const;
    
    bool loadSprites(std::ifstream& levelFile, LevelMap& levelMap, unsigned int count);
    static void loadTiles(std::ifstream& levelFile, LevelMap& levelMap);
    void disposeSpritesUnused(std::map<ObjectType, std::vector<unsigned int>>& spriteSetsUsed);
  public:
    LevelManager(SpriteManager& spriteManager, ResourceManager& resourceManager, Screen& screen);
    bool initialize() override;

    [[maybe_unused]] unsigned long getRealmsCount();
    [[maybe_unused]] void getRealm(LevelRealm& realm, unsigned int realmId);
    [[maybe_unused]] LevelRealm getRealm(unsigned int realmId);
  
    bool load(LevelMap& levelMap, unsigned int realmId, unsigned int levelId);
};

#endif /* LevelManager_h */
