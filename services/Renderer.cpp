//
//  Renderer.cpp
//  MeowMeow
//
//  Created by Alex Serdukov on 06.04.2022.
//  Copyright © 2022 Alex Serdukov. All rights reserved.
//

#include "Renderer.h"
#include "../Application.h"

Renderer::Renderer(Application& app) :
  resourceManager(app.getResourceManager()), 
  screen(app.getScreen()),
  window(app.getWindow()),
  settingsManager(app.getSettingsManager()),
  subject(app.getStateManager()) {}

bool Renderer::initialize() {
  using namespace sf;
  
  Image appIcon{};
  bool initialized = resourceManager.load(appIcon, "icons/appIcon");
  
  if (initialized) {
    const std::string& windowTitle = settingsManager.windowTitle;
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
