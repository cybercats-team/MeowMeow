//
//  SceneContainer.hpp
//  MeowMeow
//
//  Created by Alex Serdukov on 11.04.2021.
//  Copyright © 2021 Alex Serdukov. All rights reserved.
//

#ifndef Container_h
#define Container_h

#include "primitives/Screen.h"
#include "interfaces/SceneController.h"

#include "services/ResourceManager.h"
#include "services/SpriteManager.h"
#include "services/LevelManager.h"

class Container {
  private:
    Screen& screen;
    ResourceManager& resourceManager;
    SpriteManager spriteManager;
    LevelManager levelManager;
  
    friend class AppState;
    friend class SceneController;
    friend class Application; // TODO: remove
  public:
    Container(Screen& screen, ResourceManager& resourceManager);
    bool initialize();
};

#endif /* Container_h */
