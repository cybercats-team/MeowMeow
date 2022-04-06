//
// Created by cyberneticist on 20.01.21.
//

#include "Application.h"

#include <utility>

Application::Application(std::string appName, Platform& platform) :
  screen(),
  platform(platform),
  appName(appName),
  resourceManager(platform),
  spriteManager(resourceManager, screen),
  levelManager(spriteManager, resourceManager, screen),
  stateManager(*this),
  renderer(stateManager, window) {}

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

bool Application::initialize() {
  using namespace std;
  using namespace sf;

  Image appIcon{};
  
  array<reference_wrapper<Initializable>, 4> modules = {
    screen, spriteManager, levelManager, stateManager
  };
  
  bool initialized = resourceManager.load(appIcon, "icons/appIcon")
    && all_of(modules.begin(), modules.end(), [](Initializable& module) {
      return module.initialize();
    });

  if (initialized) {
    Vector2u size = appIcon.getSize();

    window.create(screen.selectedMode, appName, Style::Fullscreen);
    window.setIcon(size.x, size.y, appIcon.getPixelsPtr());
    window.setFramerateLimit(60);

    Debug::printf(
      "Initialized app window %dx%d \"%s\"",
      screen.getWidth(), screen.getHeight(), appName
    );
  }

  return initialized;
}

void Application::run() {
  using namespace sf;
  using namespace std;

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
    Event event{};
    stateManager.onBeforeEvents();
    
    while (window.pollEvent(event)) {
      stateManager.onEvent(event);
    }
    
    renderer.render();
  }

  stateManager.onDisposed();
}
