//
//  AppState.cpp
//  MeowMeow
//
//  Created by Alex Serdukov on 31.10.2021.
//  Copyright © 2021 Alex Serdukov. All rights reserved.
//

#include "AppState.h"

#include "controllers/SplashController.h"
#include "controllers/LevelController.h"

AppState::AppState(Container& container) :
  container(container),
  activeController(std::ref(*(new SplashController(*this)))) {}

Controller& AppState::getActiveController() {
  return (Controller&) activeController;
}

AppState::~AppState() {
  delete (Controller*) &activeController.get();
}
