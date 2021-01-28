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
  spriteManager(resourceManager, screen) {}

bool Application::initialize() {
  using namespace std;
  using namespace sf;
  
  Image appIcon;

  if (
    !screen.initialize() ||
    !spriteManager.initialize() ||
    !resourceManager.load(appIcon, "icons/appIcon")
  ) {
    return false;
  }
  
  Vector2u size = appIcon.getSize();
    
  window.create(screen.selectedMode, "SFML window", Style::Fullscreen);
  window.setIcon(size.x, size.y, appIcon.getPixelsPtr());

  return true;
}

void Application::run() {
  using namespace sf;
  using namespace std;

  Clock clock{};
  SpriteSet grassSet{};
  SpriteSet fenceSet{};
  
  if (
      !spriteManager.load(grassSet, ObjectType::Terrain, 0) ||
      !spriteManager.load(fenceSet, ObjectType::Terrain, 1)
  ) {
    window.close();
    return;
  }
  
  SpriteObject grass{};
  SpriteObject fence[6] = {
    SpriteObject(),
    SpriteObject(),
    SpriteObject(),
    SpriteObject(),
    SpriteObject(),
    SpriteObject()
  };
  
  grassSet.getSprite(grass, 0);
  
  for (int i = 0; i < 6; i++) {
    fenceSet.getSprite(fence[i], i);
  }
  
  const Int64 frameInterval = (Int64) (1000.0 * (
    (float) grass.getAnimationDuration() /
    (float) grass.getFramesCount()
  ));
  
  debugPrint("Frame interval " + to_string(frameInterval));
  
  const unsigned int width = grassSet.getSpriteWidth();
  const unsigned int height = grassSet.getSpriteHeight();
  const unsigned int tilesX = screen.getWidth() / width;
  const unsigned int tilesY = screen.getHeight() / height;
  
  debugPrint("Sprite size " + to_string(width) + "x" + to_string(height));

  // Start the game loop
  while (window.isOpen())
  {
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
      }
    

      if (clock.getElapsedTime().asMicroseconds() >= frameInterval) {
        grass.nextFrame();
        clock.restart();
      }        

      // Clear screen
      window.clear();
      

      // Draw the sprite
      for (unsigned int x = 0; x < tilesX; x++) {
        for (unsigned int y = 0; y < tilesY; y++) {
          for (int i = 0; i < 6; i++) {
            fence[i].setPosition(x * width, y * height);
          }
          
          grass.setPosition(x * width, y * height);
          window.draw(grass);
          
          if (x == 0 && y == 0) {
            window.draw(fence[0]);
          } else if (x == (tilesX - 1) && y == 0) {
            window.draw(fence[3]);
          } else if (x == 0 && y == (tilesY - 1)) {
            window.draw(fence[2]);
          } else if (x == (tilesX - 1) && y == (tilesY - 1)) {
            window.draw(fence[5]);
          } else if (x == 0 || x == (tilesX - 1)) {
            window.draw(fence[1]);
          } else if (y == 0 || y == (tilesY - 1)) {
            window.draw(fence[4]);
          }
        }
      }
      
      // Update the window
      window.display();
  }
}
