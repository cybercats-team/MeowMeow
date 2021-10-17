//
// Created by cyberneticist on 20.01.21.
//

#ifndef Application_h
#define Application_h

#include <SFML/Graphics.hpp>

#include "primitives/Screen.h"
#include "services/ResourceManager.h"
#include "services/SpriteManager.h"
#include "services/LevelManager.h"
#include "Container.h"

#include "scenes/LevelScene.h"

#include "Debug.h"

class Application {
  protected:
    explicit Application(std::string withResourcePath);
  
    static Application* instance;
    
    Screen screen;
    ResourceManager resourceManager;
    SpriteManager spriteManager;
    LevelManager levelManager;
    Container container;
    sf::RenderWindow window{};
  
  public:
    Application(Application &other) = delete;
    void operator=(const Application &) = delete;
  
    static Application* create(std::string resourcePath);
    bool initialize();
    void run();
};


#endif //Application_h
