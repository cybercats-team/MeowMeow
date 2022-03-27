//
// Created by cyberneticist on 20.01.21.
//

#ifndef Application_h
#define Application_h

#include <SFML/Graphics.hpp>

#include "Container.h"
#include "primitives/Screen.h"
#include "interfaces/Platform.h"
#include "services/ResourceManager.h"

#include "utils/Debug.h"

class Application {
  protected:
    Screen screen;
    ResourceManager resourceManager;
    Container container;
    sf::RenderWindow window{};
    std::string appName;
  
  public:
    Application(std::string appName, const std::string& withResourcePath);
  
    bool initialize();
    void run();
};

#endif //Application_h
