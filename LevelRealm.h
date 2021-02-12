//
//  LevelRealm.hpp
//  MeowMeow
//
//  Created by Alex Serdukov on 12.02.2021.
//  Copyright © 2021 Alex Serdukov. All rights reserved.
//

#ifndef LevelRealm_h
#define LevelRealm_h

#include <string>
#include <vector>

#include "TypeDefs.h"

class LevelRealm {
  private:
    std::string realmName;
    std::vector<std::string> levelNames;
    unsigned int levelsCount;
  public:
    LevelRealm(RealmInfo& realmInfo, std::vector<LevelInfo>& levels);
    [[nodiscard]] unsigned int getLevelsCount() const;
    [[nodiscard]] std::string getName() const;
    [[nodiscard]] std::string getLevelName(unsigned int level) const;
};

#endif /* LevelRealm_h */
