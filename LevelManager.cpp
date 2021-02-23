//
//  LevelManager.cpp
//  MeowMeow
//
//  Created by Alex Serdukov on 16.02.2021.
//  Copyright © 2021 Alex Serdukov. All rights reserved.
//

#include "LevelManager.h"

LevelManager::LevelManager(SpriteManager& spriteManager, ResourceManager& resourceManager, Screen& screen):
  BundleManager(resourceManager, screen),
  spriteManager(spriteManager),
  realms({}),
  levels({}) {}

bool LevelManager::initialize() {
  using namespace std;
  
  ifstream listFile;
  BundleHeader header{};
  RealmInfo info{};
  
  debugPrint("Loading bundle " + bundlePath);
  
  if (!resourceManager.load(listFile, header, bundlePath)) {
    return false;
  }
  
  for (unsigned int realmId = 0; realmId < header.itemsCount; realmId++) {
    vector<string> pathes{};
    vector<LevelInfo> levelsList{};
    
    listFile.read((char *) &info, sizeof(info));
    
    for (unsigned int levelId = 0; levelId < info.levelsCount; levelId++) {
      LevelInfo levelInfo{};
      
      listFile.read((char *) &levelInfo, sizeof(levelInfo));
      levelsList.push_back(levelInfo);
      
      debugPrint("Added level " + string(levelInfo.path));
    }
    
    levels.push_back(levelsList);
    realms.push_back(info);
  }
  
  return true;
}

unsigned int LevelManager::getRealmsCount() {
  return realms.size();
}

void LevelManager::getRealm(LevelRealm& realm, unsigned int realmId) {
  using namespace std;
  
  RealmInfo& info = realms[realmId];
  
  realm.levelsCount = info.levelsCount;
  realm.realmName = string(info.realmName);
  
  realm.levelNames.clear();
  fillLevelNames(realm.levelNames, realmId);
}

LevelRealm LevelManager::getRealm(unsigned int realmId) {
  using namespace std;
  
  RealmInfo& info = realms[realmId];
  vector<string> levelNames;
  
  fillLevelNames(levelNames, realmId);
  
  return LevelRealm(string(info.realmName), info.levelsCount, levelNames);
}

void LevelManager::fillLevelNames(std::vector<std::string>& levelNames, unsigned int realmId) {
  using namespace std;
  
  for (auto& levelInfo: levels[realmId]) {
    levelNames.emplace_back(levelInfo.levelName);
  }
}
