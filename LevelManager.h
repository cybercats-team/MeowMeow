//
//  LevelManager.hpp
//  MeowMeow
//
//  Created by Alex Serdukov on 16.02.2021.
//  Copyright © 2021 Alex Serdukov. All rights reserved.
//

#ifndef LevelManager_h
#define LevelManager_h

#include "BundleManager.h"

class LevelManager: public BundleManager {
  public:
    LevelManager(ResourceManager& resourceManager, Screen& screen);
};

#endif /* LevelManager_h */
