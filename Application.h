//
// Created by cyberneticist on 20.01.21.
//

#ifndef Application_h
#define Application_h

#include <SFML/Graphics.hpp>

#include "primitives/Screen.h"
#include "services/ResourceManager.h"
#include "interfaces/SceneController.h"
#include "AppState.h"

#include "Debug.h"

#include "primitives/LevelMap.h" // TODO: remove
#include "scenes/LevelScene.h"  // TODO: remove

class Application {
  protected:
    explicit Application(std::string withResourcePath);
  
    static Application* instance;
    
    Screen screen;
    ResourceManager resourceManager;
    Container container;
    AppState appState;
    sf::RenderWindow window{};
  
  public:
    Application(Application &other) = delete;
    void operator=(const Application &) = delete;
  
    static Application* create(std::string resourcePath);
    bool initialize();
    void run();
};


#endif //Application_h
