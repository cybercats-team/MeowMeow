//
//  LevelRealm.cpp
//  MeowMeow
//
//  Created by Alex Serdukov on 12.02.2021.
//  Copyright © 2021 Alex Serdukov. All rights reserved.
//

#include "LevelRealm.h"

#include <utility>

LevelRealm::LevelRealm() : realmName(), levelsCount(0), levelNames({}) {}

LevelRealm::LevelRealm(std::string realmName, unsigned int levelsCount, std::vector<std::string>& levelNames) :
  levelsCount(levelsCount),
  realmName(std::move(realmName)),
  levelNames(std::move(levelNames)) {}

unsigned int LevelRealm::getLevelsCount() const {
  return levelsCount;
}

std::string LevelRealm::getName() const {
  return realmName;
}

std::string LevelRealm::getLevelName(unsigned int level) const {
  return levelNames[level];
}
