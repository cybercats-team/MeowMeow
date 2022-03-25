//
// Created by cyberneticist on 09.11.21.
//

#ifndef Controller_h
#define Controller_h

#include <SFML/Graphics.hpp>
#include "../interfaces/EventHandler.h"
#include "../interfaces/Disposable.h"

class Controller :
  public sf::Drawable,
  public EventHandler,
  public Disposable
{
  public:
    virtual bool loadResources() = 0;
};

#endif //Controller_h
