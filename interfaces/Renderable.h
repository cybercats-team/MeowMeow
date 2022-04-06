//
//  Renderable.h
//  MeowMeow
//
//  Created by Alex Serdukov on 06.04.2022.
//  Copyright © 2022 Alex Serdukov. All rights reserved.
//

#ifndef Renderable_h
#define Renderable_h

#include <SFML/Graphics.hpp>
#include "EventHandler.h"

class Renderable :
  public sf::Drawable,
  public EventHandler {};

#endif /* Renderable_h */
