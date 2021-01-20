//
// Created by cyberneticist on 20.01.21.
//

#ifndef MEOWMEOW_APPLICATION_H
#define MEOWMEOW_APPLICATION_H

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

class Application {
  
  protected:
    Application(string withResourcePath);
    ~Application();
  
    static Application* instance;
    string resourcePath;
  
    Image icon;
    Texture texture;
    Sprite sprite;
    Font font;
    Music music;
    RenderWindow* window;
  
  public:
    Application(Application &other) = delete;
    void operator=(const Application &) = delete;
  
    static Application *create(string resourcePath);
    bool initialize();
    void run();
};


#endif //MEOWMEOW_APPLICATION_H
