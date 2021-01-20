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

int Application::run() {
  // Create the main window
  RenderWindow window(VideoMode(800, 600), "SFML window");

  // Set the Icon
  Image icon;
  if (!icon.loadFromFile(resourcePath + "icon.png")) {
      return EXIT_FAILURE;
  }
  window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

  // Load a sprite to display
  Texture texture;
  if (!texture.loadFromFile(resourcePath + "cute_image.jpg")) {
      return EXIT_FAILURE;
  }
  Sprite sprite(texture);

  // Create a graphical text to display
  Font font;
  if (!font.loadFromFile(resourcePath + "sansation.ttf")) {
      return EXIT_FAILURE;
  }
  Text text("Hello SFML", font, 50);
  text.setFillColor(Color::Black);

  // Load a music to play
  Music music;
  if (!music.openFromFile(resourcePath + "nice_music.ogg")) {
      return EXIT_FAILURE;
  }

  // Play the music
  music.play();

  // Start the game loop
  while (window.isOpen())
  {
      // Process events
      Event event;
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

      // Clear screen
      window.clear();

      // Draw the sprite
      window.draw(sprite);

      // Draw the string
      window.draw(text);

      // Update the window
      window.display();
  }

  return EXIT_SUCCESS;
}
