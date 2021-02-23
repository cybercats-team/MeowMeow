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

#include "BundleManager.h"
#include "SpriteManager.h"
#include "TypeDefs.h"
#include "LevelRealm.h"

class LevelManager: public BundleManager {
  private:
    const std::string bundlePath = "levels";
    std::vector<RealmInfo> realms;
    std::vector<std::vector<LevelInfo>> levels;
    SpriteManager& spriteManager;

  void fillLevelNames(std::vector<std::string>& levelNames, unsigned int realmId);
  public:
    LevelManager(SpriteManager& spriteManager, ResourceManager& resourceManager, Screen& screen);
    bool initialize() override;
    
    unsigned int getRealmsCount();
    void getRealm(LevelRealm& realm, unsigned int realmId);
    LevelRealm getRealm(unsigned int realmId);
  
    
};

#endif /* LevelManager_h */
