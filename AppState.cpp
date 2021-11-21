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

bool AppState::initialize() {
  Controller& activeController = getActiveController();
  
  return initializeController(activeController);
}

bool AppState::showSplash() {
  SplashController* splashController = new SplashController(*this);
  
  return setActiveController(splashController);
}

bool AppState::loadLevel(unsigned int realmId, unsigned int levelId) {
  LevelController* levelController = new LevelController(*this, realmId, levelId);
  
  return setActiveController(levelController);
}

Controller& AppState::getActiveController() {
  return (Controller&) activeController;
}

bool AppState::setActiveController(Controller* controller) {
  std::reference_wrapper<Controller> controllerRef = std::ref(*controller);
  bool initialized = initializeController((Controller&) controllerRef);
  
  if (initialized) {
    disposeController();
    activeController = controllerRef;
  } else {
    delete controller;
  }
  
  return initialized;
}

bool AppState::initializeController(Controller& controller) {
  return controller.loadResources();
}

void AppState::disposeController() {
  delete (Controller*) &activeController.get();
}

AppState::~AppState() {
  disposeController();
}
