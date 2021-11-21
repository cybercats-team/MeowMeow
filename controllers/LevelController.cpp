//
//  LevelController.cpp
//  MeowMeow
//
//  Created by Alex Serdukov on 18.10.2021.
//  Copyright © 2021 Alex Serdukov. All rights reserved.
//

#include "LevelController.h"

LevelController::LevelController(AppState& appState, unsigned int realmId, unsigned int levelId) :
  SceneController(appState), realmId(realmId), levelId(levelId), levelMap(), levelScene(levelMap) {}

bool LevelController::loadResources() {
  LevelManager& levelManager = container.levelManager;
  bool loaded = levelManager.load(levelMap, realmId, levelId);
  
  if (loaded) {
    levelScene.onMapLoaded();
    pushScene(levelScene);
  }
  
  return loaded;
}
