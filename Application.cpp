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

  Font font;
  Texture texture;
  Music music;
  Clock clock;

  resourceManager.load(font, "sansation");
  resourceManager.load(texture, "skybox/landscape");
  resourceManager.load(music, "intro_theme");

  Sprite sprite(texture);
  Text text("Hello SFML", font, 50);
  text.setFillColor(Color::Black);
  
  float i = 0;
  const Int64 oneBySixty = 1000000 / 60;

  // Play the music
  music.play();

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
    

      if (clock.getElapsedTime().asMicroseconds() >= oneBySixty) {
        sprite.setPosition(i, i);

        // Clear screen
        window.clear();

        // Draw the sprite
        window.draw(sprite);

        // Draw the string
        window.draw(text);

        // Update the window
        window.display();

        i++;
        if (i > 1000) i = 0;

        clock.restart();
      }
  }
}
