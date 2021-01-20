//
// Created by cyberneticist on 20.01.21.
//

#include "Application.h"

Application* Application::instance = nullptr;

Application* Application::create(string resourcePath) {
  if (instance == nullptr) {
    instance = new Application(resourcePath);
  }
  
  return instance;
}

Application::Application(string withResourcePath) :
  resourcePath(withResourcePath),
  icon(),
  texture(),
  font(),
  sprite(),
  music() {}

bool Application::initialize() {
  if (!icon.loadFromFile(resourcePath + "icon.png") ||
    !texture.loadFromFile(resourcePath + "cute_image.jpg") ||
    !font.loadFromFile(resourcePath + "sansation.ttf") ||
    !music.openFromFile(resourcePath + "nice_music.ogg")
  ) {
    return false;
  }
  
  vector<VideoMode> modes = VideoMode::getFullscreenModes();
  
  window = new RenderWindow(modes[0], "SFML window", Style::Fullscreen);
  window->setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
  
  sprite.setTexture(texture);
  
  return true;
}

void Application::run() {
  Text text("Hello SFML", font, 50);
  text.setFillColor(Color::Black);

  // Play the music
  music.play();

  // Start the game loop
  while (window->isOpen())
  {
      // Process events
      Event event;
      while (window->pollEvent(event))
      {
          // Close window: exit
          if (event.type == Event::Closed) {
              window->close();
          }

          // Escape pressed: exit
          if (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape) {
              window->close();
          }
      }

      // Clear screen
      window->clear();

      // Draw the sprite
      window->draw(sprite);

      // Draw the string
      window->draw(text);

      // Update the window
      window->display();
  }
}

Application::~Application() {
  delete window;
}
