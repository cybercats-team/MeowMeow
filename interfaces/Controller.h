//
// Created by cyberneticist on 09.11.21.
//

#ifndef Controller_h
#define Controller_h

#include <SFML/Graphics.hpp>

#include "EventHandler.h"
#include "Disposable.h"
#include "Initializable.h"

class Controller :
  public sf::Drawable,
  public EventHandler,
  public Disposable,
  public Initializable {};

#endif //Controller_h
