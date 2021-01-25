//
// Created by cyberneticist on 20.01.21.
//

#ifndef MEOWMEOW_APPLICATION_H
#define MEOWMEOW_APPLICATION_H

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

#include "ResourceManager.h"
#include "SpriteManager.h"

class Application {

  protected:

    explicit Application(std::string withResourcePath);
    ~Application();
  
    static Application* instance;
    ResourceManager resourceManager;
    SpriteManager textureManager;
    sf::RenderWindow* window = nullptr;
  
  public:
    Application(Application &other) = delete;
    void operator=(const Application &) = delete;
  
    static Application *create(std::string resourcePath);
    bool initialize();
    void run();
};


#endif //MEOWMEOW_APPLICATION_H
