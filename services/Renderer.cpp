//
//  Renderer.cpp
//  MeowMeow
//
//  Created by Alex Serdukov on 06.04.2022.
//  Copyright © 2022 Alex Serdukov. All rights reserved.
//

#include "Renderer.h"

Renderer::Renderer(
  ResourceManager& resourceManager,
  Screen& screen,
  sf::RenderWindow& window,
  std::string windowTitle,
  Renderable& subject
) :
  resourceManager(resourceManager),
  screen(screen),
  window(window),
  windowTitle(windowTitle),
  subject(subject)
{}

bool Renderer::initialize() {
  using namespace sf;
  
  Image appIcon{};
  bool initialized = resourceManager.load(appIcon, "icons/appIcon");
  
  if (initialized) {
    Vector2u size = appIcon.getSize();

    window.create(screen.selectedMode, windowTitle, Style::Fullscreen);
    window.setIcon(size.x, size.y, appIcon.getPixelsPtr());
    window.setFramerateLimit(60);

    Debug::printf(
      "Initialized app window %dx%d \"%s\"",
      screen.getWidth(), screen.getHeight(), windowTitle
    );
  }
  
  return initialized;
}

void Renderer::render() {
  window.clear();
  subject.onBeforeRender();
  
  // Draw the scenes
  window.draw(subject);
  // Update the window
  window.display();
}
