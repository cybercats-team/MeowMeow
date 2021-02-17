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
  levelManager(resourceManager, screen) {}

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
  window.setFramerateLimit(60);

  return true;
}

void Application::run() {
  using namespace sf;
  using namespace std;

  Clock clock{};
  SpriteSet grassSet{};
  SpriteSet boxSet{};
  SpriteSet waterSet{};
  
  if (
      !spriteManager.load(grassSet, ObjectType::Terrain, 0) ||
      !spriteManager.load(boxSet, ObjectType::Terrain, 1) ||
      !spriteManager.load(waterSet, ObjectType::Terrain, 2)
  ) {
    window.close();
    return;
  }
  
  SpriteObject grass{};
  grassSet.getSprite(grass, 0);
  
  vector<SpriteObject> box{};
  for (int i = 0; i < 3; i++) {
    box.push_back(boxSet.getSprite(i));
  }
  
  vector<SpriteObject> water{};
  for (int i = 0; i < 16; i++) {
    water.push_back(waterSet.getSprite(i));
  }
  
  const Int64 frameInterval = (Int64) (1000.0 * (
    (float) water[0].getAnimationDuration() /
    (float) water[0].getFramesCount()
  ));
  
  debugPrint("Frame interval " + to_string(frameInterval));
  
  const unsigned int width = grassSet.getSpriteWidth();
  const unsigned int height = grassSet.getSpriteHeight();
  const unsigned int tilesX = screen.getWidth() / width;
  const unsigned int tilesY = screen.getHeight() / height;
  
  debugPrint("Sprite size " + to_string(width) + "x" + to_string(height));
  debugPrint("Tiles count " + to_string(tilesX) + "x" + to_string(tilesY));

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
        for (auto& sprite: water) {
          sprite.nextFrame();
        }
        
        clock.restart();
      }

      // Clear screen
      window.clear();

      // Draw the map
      for (unsigned int x = 0; x < tilesX; x++) {
        for (unsigned int y = 0; y < tilesY; y++) {
          grass.setPosition(x * width, y * height);
          window.draw(grass);
          
          // Draw corners
          if ((x == 0 || x == tilesX - 1) && (y == 0 || y == tilesY - 1)) {
            box[2].setPosition(x * width, y * height);
            window.draw(box[2]);
          } else if (x == 0 || x == tilesX - 1 || y == 0 || y == tilesY - 1) {
            // Draw borders
            box[(x + y) % 4 == 0 ? 0 : 1].setPosition(x * width, y * height);
            window.draw(box[(x + y) % 4 == 0 ? 0 : 1]);
          }
        }
      }
    
      // Draw the lake
      for (unsigned int y = 0; y < 4; y++) {
        for (unsigned int x = 0; x < 4; x++) {
          water[4 * y + x].setPosition((5 + x) * width, (5 + y) * height);
          window.draw(water[4 * y + x]);
        }
      }
      
      // Update the window
      window.display();
  }
}
