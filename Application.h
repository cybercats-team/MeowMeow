//
// Created by cyberneticist on 20.01.21.
//

#ifndef Application_h
#define Application_h

#include <SFML/Graphics.hpp>
#include <array>
#include <algorithm>
#include <functional>

#include "primitives/Screen.h"
#include "interfaces/Platform.h"
#include "interfaces/Initializable.h"

#include "services/ResourceManager.h"
#include "services/ResourceManager.h"
#include "services/SpriteManager.h"
#include "services/LevelManager.h"
#include "services/StateManager.h"
#include "services/EventManager.h"
#include "services/Renderer.h"

#include "utils/Debug.h"

class Application {
  protected:
    sf::RenderWindow window{};    
    Screen screen;
    Platform& platform;
    ResourceManager resourceManager;
    SpriteManager spriteManager;
    LevelManager levelManager;
    StateManager stateManager;
    EventManager eventManager;
    Renderer renderer;
  public:
    Application(std::string appName, Platform& platform);
  
    sf::RenderWindow& getWindow();
    const Screen& getScreen() const;
    const ResourceManager& getResourceManager() const;
    const SpriteManager& getSpriteManager() const;
    LevelManager& getLevelManager();
    const Renderer& getRenderer() const;
    const EventManager& getEventManager() const;

    bool initialize();
    void run();
};

#endif //Application_h
