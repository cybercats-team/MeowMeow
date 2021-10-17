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

#include "../interfaces/TypeDefs.h"

class LevelRealm {
  private:
    std::string realmName;
    std::vector<std::string> levelNames;
    unsigned int levelsCount;
  
    friend class LevelManager;
  public:
    LevelRealm();
    LevelRealm(std::string realmName, unsigned int levelsCount, std::vector<std::string>& levelNames);
    [[nodiscard]] unsigned int getLevelsCount() const;
    [[nodiscard]] std::string getName() const;
    [[nodiscard]] std::string getLevelName(unsigned int level) const;
};

#endif /* LevelRealm_h */
