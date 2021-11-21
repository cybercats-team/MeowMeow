//
// Created by cyberneticist on 20.01.21.
//

#ifndef Application_h
#define Application_h

#include <SFML/Graphics.hpp>

#include "primitives/Screen.h"
#include "services/ResourceManager.h"
#include "AppState.h"

#include "Debug.h"

class Application {
  protected:
    Screen screen;
    ResourceManager resourceManager;
    Container container;
    AppState appState;
    sf::RenderWindow window{};
    std::string appName;
  
  public:
    Application(const std::string& appName, const std::string& withResourcePath);
  
    bool initialize();
    void run();
};

#endif //Application_h
