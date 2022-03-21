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
  activeController(nullptr) {}

bool AppState::initialize() {
  return showSplash();
}

bool AppState::hasActiveController() const {
  return nullptr != activeController.get();
}

Controller& AppState::getActiveController() const {
  return *activeController.get();
}

bool AppState::setActiveController(Controller* controller) {
  std::unique_ptr<Controller> controllerPtr(controller);
  bool initialized = controllerPtr->loadResources();

  if (initialized) {
    activeController = std::move(controllerPtr);
  }

  debugPrint("Active controller updated");
  return initialized;
}

void AppState::onEvent(sf::Event& event) {
  if (!hasActiveController()) {
    return;
  }

  getActiveController().onEvent(event);
}

void AppState::onBeforeRender() {
  if (!hasActiveController()) {
    return;
  }

  getActiveController().onBeforeRender();
}

void AppState::draw(sf::RenderTarget& target, sf::RenderStates states) const {
  if (!hasActiveController()) {
    return;
  }

  target.draw(getActiveController());
}

bool AppState::showSplash() {
  auto* splashController = new SplashController(*this);

  return setActiveController(splashController);
}

bool AppState::loadLevel(unsigned int realmId, unsigned int levelId) {
  auto* levelController = new LevelController(*this, realmId, levelId);

  return setActiveController(levelController);
}
