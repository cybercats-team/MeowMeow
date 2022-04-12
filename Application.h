//
// Created by cyberneticist on 20.01.21.
//

#ifndef Application_h
#define Application_h

#include <SFML/Graphics.hpp>
#include <algorithm>
#include <array>
#include <functional>
#include <utility>

#include "interfaces/Initializable.h"
#include "interfaces/Platform.h"
#include "primitives/Screen.h"

#include "services/EventManager.h"
#include "services/LevelManager.h"
#include "services/Renderer.h"
#include "services/ResourceManager.h"
#include "services/SettingsManager.h"
#include "services/SpriteManager.h"
#include "services/StateManager.h"

#include "utils/Debug.h"

class Application
{
  protected:
  sf::RenderWindow window {};
  Screen screen;
  Platform& platform;
  SettingsManager settingsManager;
  ResourceManager resourceManager;
  SpriteManager spriteManager;
  LevelManager levelManager;
  StateManager stateManager;
  EventManager eventManager;
  Renderer renderer;

  public:
  explicit Application(Platform& platform);

  sf::RenderWindow& getWindow();
  const Screen& getScreen() const;
  ResourceManager& getResourceManager();
  const SpriteManager& getSpriteManager() const;
  SettingsManager& getSettingsManager();
  LevelManager& getLevelManager();
  const Renderer& getRenderer() const;
  const EventManager& getEventManager() const;
  StateManager& getStateManager();

  bool initialize();
  void run();
};

#endif // Application_h
