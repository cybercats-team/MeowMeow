//
//  LevelController.hpp
//  MeowMeow
//
//  Created by Alex Serdukov on 18.10.2021.
//  Copyright © 2021 Alex Serdukov. All rights reserved.
//

#ifndef LevelController_h
#define LevelController_h

#include "../primitives/LevelMap.h"
#include "../scenes/LevelScene.h"
#include "../ui/SceneController.h"

class LevelController :
  public SceneController
{
  private:
    unsigned int realmId;
    unsigned int levelId;
    LevelMap levelMap;
    LevelScene levelScene;
  
  public:
    LevelController(AppState& appState, unsigned int realmId, unsigned int levelId);
    bool loadResources() override;
};

#endif /* LevelController_h */
