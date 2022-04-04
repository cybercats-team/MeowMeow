//
//  SceneContainer.cpp
//  MeowMeow
//
//  Created by Alex Serdukov on 11.04.2021.
//  Copyright © 2021 Alex Serdukov. All rights reserved.
//

#include "StateManager.h"
#include "../controllers/SplashController.h"
#include "../controllers/LevelController.h"

StateManager::StateManager(Application& app) :
  app(app), activeController(nullptr) {}

bool StateManager::initialize() {
  return showSplash();
}

bool StateManager::hasActiveController() const {
  return nullptr != activeController.get();
}

Controller& StateManager::getActiveController() const {
  return *activeController.get();
}

bool StateManager::setActiveController(Controller* controller) {
  std::unique_ptr<Controller> controllerPtr(controller);
  bool initialized = controllerPtr->initialize();

  if (initialized) {
    disposeActiveController();
    activeController = std::move(controllerPtr);
  } else {
    controllerPtr->onDisposed();
  }

  return initialized;
}

void StateManager::disposeActiveController() {
  if (hasActiveController()) {
    getActiveController().onDisposed();
  }
}

void StateManager::onDisposed() {
  disposeActiveController();
}

void StateManager::onBeforeEvents() {
  if (!hasActiveController()) {
    return;
  }

  getActiveController().onBeforeEvents();
}

void StateManager::onEvent(sf::Event& event) {
  using namespace sf;
  
  if (
    // Close window: exit
    (event.type == Event::Closed) ||
    // Escape pressed: exit
    (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape)
  ) {
    exitApp();
    return;
  }
  
  if (!hasActiveController()) {
    return;
  }

  getActiveController().onEvent(event);
}

void StateManager::onBeforeRender() {
  if (!hasActiveController()) {
    return;
  }

  getActiveController().onBeforeRender();
}

void StateManager::draw(sf::RenderTarget& target, sf::RenderStates states) const {
  if (!hasActiveController()) {
    return;
  }

  target.draw(getActiveController());
}

bool StateManager::showSplash() {
  auto* splashController = new SplashController(app);

  return setActiveController(splashController);
}

bool StateManager::loadLevel(unsigned int realmId, unsigned int levelId) {
  auto* levelController = new LevelController(app, realmId, levelId);

  return setActiveController(levelController);
}

void StateManager::exitApp() {
  sf::RenderWindow& window = app.getWindow();
    
  window.close();
}
