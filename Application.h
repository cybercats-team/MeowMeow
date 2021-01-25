//
// Created by cyberneticist on 20.01.21.
//

#ifndef MEOWMEOW_APPLICATION_H
#define MEOWMEOW_APPLICATION_H

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

#include "Screen.h"
#include "ResourceManager.h"
#include "SpriteManager.h"

#include "Debug.h"

class Application {
  protected:
    explicit Application(std::string withResourcePath);
  
    static Application* instance;
    
    Screen screen;
    SpriteManager spriteManager;
    ResourceManager resourceManager;
    sf::RenderWindow window{};
  
  public:
    Application(Application &other) = delete;
    void operator=(const Application &) = delete;
  
    static Application *create(std::string resourcePath);
    bool initialize();
    void run();
};


#endif //MEOWMEOW_APPLICATION_H
