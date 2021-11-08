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
    Application(std::string appName, const std::string& withResourcePath);
  
    static Application* instance;
    
    Screen screen;
    ResourceManager resourceManager;
    Container container;
    AppState appState;
    sf::RenderWindow window{};
    std::string appName;
  
  public:
    Application(Application &other) = delete;
    void operator=(const Application &) = delete;
  
    static Application* create(const std::string& appName, const std::string& resourcePath);
    bool initialize();
    void run();
};


#endif //Application_h
