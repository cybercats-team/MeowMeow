//
//  LevelRealm.cpp
//  MeowMeow
//
//  Created by Alex Serdukov on 12.02.2021.
//  Copyright © 2021 Alex Serdukov. All rights reserved.
//

#include "LevelRealm.h"

LevelRealm::LevelRealm(RealmInfo& realmInfo, std::vector<LevelInfo>& levels) :
  realmName(realmInfo.realmName),
  levelsCount(realmInfo.levelsCount),
  levelNames({})
{
  for (auto& levelInfo: levels) {
    std::string levelName(levelInfo.levelName);
      
    levelNames.push_back(levelName);
  }
}

unsigned int LevelRealm::getLevelsCount() const {
  return levelsCount;
}

std::string LevelRealm::getName() const {
  return realmName;
}

std::string LevelRealm::getLevelName(unsigned int level) const {
  return levelNames[level];
}
