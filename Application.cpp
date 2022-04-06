//
// Created by cyberneticist on 20.01.21.
//

#include "Application.h"

#include <utility>

Application::Application(std::string appName, Platform& platform) :
  screen(),
  platform(platform),
  resourceManager(platform),
  spriteManager(resourceManager, screen),
  levelManager(spriteManager, resourceManager, screen),
  stateManager(*this),
  eventManager(window, stateManager),
  renderer(resourceManager, screen, window, appName, stateManager) {}

sf::RenderWindow& Application::getWindow() {
  return window;
}

const Screen& Application::getScreen() const {
  return screen;
}

const ResourceManager& Application::getResourceManager() const {
  return resourceManager;
}

const SpriteManager& Application::getSpriteManager() const {
  return spriteManager;
}

LevelManager& Application::getLevelManager() {
  return levelManager;
}

const Renderer& Application::getRenderer() const {
  return renderer;
}

const EventManager& Application::getEventManager() const {
  return eventManager;
}

bool Application::initialize() {
  using namespace std;
  
  array<reference_wrapper<Initializable>, 6> modules = {
    screen,
    renderer,
    spriteManager,
    levelManager,
    stateManager,
    eventManager
  };
  
  return all_of(modules.begin(), modules.end(), [](Initializable& module) {
    return module.initialize();
  });
}

void Application::run() {
  /* TODO: remove */
  if (!stateManager.loadLevel(0, 0)) {
    stateManager.exitApp();
    return;
  }
  /* /TODO: */

  // Start the game loop
  while (window.isOpen())
  {
    // Process events
    eventManager.processEvents();
    // update window
    renderer.render();
  }

  stateManager.onDisposed();
}
