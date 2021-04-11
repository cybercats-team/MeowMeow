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
  spriteManager(resourceManager, screen),
  levelManager(spriteManager, resourceManager, screen),
  container(screen) {}

bool Application::initialize() {
  using namespace std;
  using namespace sf;
  
  Image appIcon;

  if (
    !screen.initialize() ||
    !spriteManager.initialize() ||
    !levelManager.initialize() ||
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

  LevelMap level{};
  
  if (!levelManager.load(level, 0, 0)) {
    window.close();
    return;
  }
  
  LevelScene scene(level);
  
  // push scene to the container
  container.pushScene(scene);
  
  /*const Int64 frameInterval = (Int64) (1000.0 * (
    (float) water[0].getAnimationDuration() /
    (float) water[0].getFramesCount()
  ));
  
  debugPrint("Frame interval " + to_string(frameInterval));*/
  
  // Start the game loop
  while (window.isOpen())
  {
      container.onBeforeEvent();
    
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
        
          container.onEvent(event);
      }

      /*if (clock.getElapsedTime().asMicroseconds() >= frameInterval) {
        for (auto& sprite: water) {
          sprite.nextFrame();
        }
        
        clock.restart();
      }*/

      // Clear screen
      window.clear();
    
      container.onBeforeRender();
    
      // Draw the scenes
      window.draw(container);
            
      // Update the window
      window.display();
  }
}
