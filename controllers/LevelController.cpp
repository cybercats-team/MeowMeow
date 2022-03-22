//
//  LevelController.cpp
//  MeowMeow
//
//  Created by Alex Serdukov on 18.10.2021.
//  Copyright © 2021 Alex Serdukov. All rights reserved.
//

#include "LevelController.h"

LevelController::LevelController(Container& container, unsigned int realmId, unsigned int levelId) :
  SceneController(container), realmId(realmId), levelId(levelId), levelMap(), levelScene(levelMap) {}

bool LevelController::loadResources() {
  LevelManager& levelManager = container.getLevelManager();
  bool loaded = levelManager.load(levelMap, realmId, levelId);
  
  if (loaded) {
    levelScene.onMapLoaded();
    present(levelScene);
  }
  
  return loaded;
}
