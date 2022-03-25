//
//  SceneContainer.cpp
//  MeowMeow
//
//  Created by Alex Serdukov on 11.04.2021.
//  Copyright © 2021 Alex Serdukov. All rights reserved.
//

#include "Container.h"
#include "controllers/SplashController.h"
#include "controllers/LevelController.h"

Container::Container(Screen& screen, ResourceManager& resourceManager) :
  screen(screen), resourceManager(resourceManager),
  spriteManager(resourceManager, screen),
  levelManager(spriteManager, resourceManager, screen),
  activeController(nullptr) {}

bool Container::initialize() {
  return spriteManager.initialize()
    && levelManager.initialize()
    && showSplash();
}

bool Container::hasActiveController() const {
  return nullptr != activeController.get();
}

Controller& Container::getActiveController() const {
  return *activeController.get();
}

bool Container::setActiveController(Controller* controller) {
  std::unique_ptr<Controller> controllerPtr(controller);
  bool initialized = controllerPtr->loadResources();

  if (initialized) {
    disposeActiveController();
    activeController = std::move(controllerPtr);
  } else {
    controllerPtr->onDisposed();
  }

  return initialized;
}

void Container::disposeActiveController() {
  if (hasActiveController()) {
    getActiveController().onDisposed();
  }
}

void Container::onDisposed() {
  disposeActiveController();
}

void Container::onEvent(sf::Event& event) {
  if (!hasActiveController()) {
    return;
  }

  getActiveController().onEvent(event);
}

void Container::onBeforeRender() {
  if (!hasActiveController()) {
    return;
  }

  getActiveController().onBeforeRender();
}

void Container::draw(sf::RenderTarget& target, sf::RenderStates states) const {
  if (!hasActiveController()) {
    return;
  }

  target.draw(getActiveController());
}

const Screen& Container::getScreen() const {
  return screen;
}

const ResourceManager& Container::getResourceManager() const {
  return resourceManager;
}

const SpriteManager& Container::getSpriteManager() const {
  return spriteManager;
}

LevelManager& Container::getLevelManager() {
  return levelManager;
}

bool Container::showSplash() {
  auto* splashController = new SplashController(*this);

  return setActiveController(splashController);
}

bool Container::loadLevel(unsigned int realmId, unsigned int levelId) {
  auto* levelController = new LevelController(*this, realmId, levelId);

  return setActiveController(levelController);
}
