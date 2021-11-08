//
// Created by cyberneticist on 20.01.21.
//

#include "Application.h"

#include <utility>

Application* Application::instance = nullptr;

Application* Application::create(const std::string& appName, const std::string& resourcePath) {
  if (instance == nullptr) {
    instance = new Application(appName, resourcePath);
  }
  
  return instance;
}

Application::Application(std::string appName, const std::string& withResourcePath) :
  screen(),
  appName(std::move(appName)),
  resourceManager(withResourcePath),
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
    
  window.create(screen.selectedMode, appName, Style::Fullscreen);
  window.setIcon(size.x, size.y, appIcon.getPixelsPtr());
  window.setFramerateLimit(60);

  debugPrint(
    "Initialized app window " +
    to_string(screen.getWidth()) + "x" +
    to_string(screen.getHeight()) +
    " \"" + appName +"\""
  );

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
