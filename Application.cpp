//
// Created by cyberneticist on 20.01.21.
//

#include "Application.h"

#include <utility>

Application::Application(std::string appName, const std::string& withResourcePath) :
  screen(),
  appName(std::move(appName)),
  resourceManager(withResourcePath),
  container(screen, resourceManager) {}

bool Application::initialize() {
  using namespace std;
  using namespace sf;

  Image appIcon;

  if (
    !resourceManager.load(appIcon, "icons/appIcon") ||
    !screen.initialize() ||
    !container.initialize()
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
  if (!container.loadLevel(0, 0)) {
    window.close();
    return;
  }
  /* /TODO: */

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

      container.onEvent(event);
    }

    window.clear();

    container.onBeforeRender();

    // Draw the scenes
    window.draw(container);

    // Update the window
    window.display();
  }
}
