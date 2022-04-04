//
//  LevelController.cpp
//  MeowMeow
//
//  Created by Alex Serdukov on 18.10.2021.
//  Copyright © 2021 Alex Serdukov. All rights reserved.
//

#include "LevelController.h"
#include "../Application.h"

LevelController::LevelController(Application& app, unsigned int realmId, unsigned int levelId) :
  SceneController(app), realmId(realmId), levelId(levelId), levelMap(), levelScene(levelMap) {}

bool LevelController::initialize() {
  LevelManager& levelManager = app.getLevelManager();
  bool loaded = levelManager.load(levelMap, realmId, levelId);

  if (loaded) {
    levelScene.onMapLoaded();
    present(levelScene);
  }

  return loaded;
}
