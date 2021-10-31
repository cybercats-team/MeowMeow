//
// Created by cyberneticist on 20.01.21.
//

#include "Application.h"

Application* Application::instance = nullptr;

Application* Application::create(std::string resourcePath) {
  using namespace std;

  if (instance == nullptr) {
    instance = new Application(move(resourcePath));
  }
  
  return instance;
}

Application::Application(std::string withResourcePath) :
  screen(),
  resourceManager(std::move(withResourcePath)),
  container(screen, resourceManager),
  appState(container) {}

bool Application::initialize() {
  using namespace std;
  using namespace sf;
  
  Image appIcon;

  if (
    !screen.initialize() ||
    !container.initialize() ||
    !resourceManager.load(appIcon, "icons/appIcon")
  ) {
    return false;
  }
  
  Vector2u size = appIcon.getSize();
    
  window.create(screen.selectedMode, "SFML window", Style::Fullscreen);
  window.setIcon(size.x, size.y, appIcon.getPixelsPtr());
  window.setFramerateLimit(60);

  return true;
}

void Application::run() {
  using namespace sf;
  using namespace std;
  
  /* TODO: remove */
  LevelMap level{};

  if (!container.levelManager.load(level, 0, 0)) {
    window.close();
    return;
  }

  LevelScene scene(level);
  
  appState.activeController.present(scene);
  /* /TODO: */
  
  // Start the game loop
  while (window.isOpen())
  {
    SceneController& controller = appState.activeController;
    
    controller.onBeforeEvent();
    
    // Process events
    Event event{};
    
    while (window.pollEvent(event))
    {
      // Close window: exit
      if (event.type == Event::Closed) {
        window.close();
      }

      // Escape pressed: exit
      if (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape) {
        window.close();
      }
    
      controller.onEvent(event);
    }

    window.clear();
  
    controller.onBeforeRender();
  
    // Draw the scenes
    window.draw(controller);
          
    // Update the window
    window.display();
  }
}
