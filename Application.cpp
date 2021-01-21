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
  resourceManager(withResourcePath) {}

bool Application::initialize() {
  /*if (!icon.loadFromFile(resourcePath + "icon.png") ||
    !texture.loadFromFile(resourcePath + "cute_image.jpg") ||
    !font.loadFromFile(resourcePath + "sansation.ttf") ||
    !music.openFromFile(resourcePath + "nice_music.ogg")
  ) {
    return false;
  }*/
  
  Image appIcon;
  vector<VideoMode> modes = VideoMode::getFullscreenModes();
  
  if (modes.empty()) {
    return false;
  }
  
  try {
    appIcon = resourceManager.loadImage("icons/appIcon.png");
  } catch (...) {
    return false;
  }
  
  Vector2u size = appIcon.getSize();
    
  window = new RenderWindow(modes[0], "SFML window", Style::Fullscreen);
  window->setIcon(size.x, size.y, appIcon.getPixelsPtr());
  
  //sprite.setTexture(texture);
  return true;
}

void Application::run() {
  Font font = resourceManager.loadFont("sansation.ttf");
  Texture texture = resourceManager.loadTexture("skybox/landscape.png");
  //Music music = resourceManager.loadMusic("intro_theme.ogg");
  
  Sprite sprite(texture);
  Text text("Hello SFML", font, 50);
  text.setFillColor(Color::Black);
  
  int i = 0;

  // Play the music
  //music.play();

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
    
      sprite.setPosition(i, i);

      // Clear screen
      window->clear();

      // Draw the sprite
      window->draw(sprite);

      // Draw the string
      window->draw(text);      
    
      // Update the window
      window->display();
    
      i++;
      if (i > 1000) i = 0;
  }
}

Application::~Application() {
  delete window;
}
