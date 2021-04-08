//
//  Scene.h
//  MeowMeow
//
//  Created by Alex Serdukov on 08.04.2021.
//  Copyright © 2021 Alex Serdukov. All rights reserved.
//

#ifndef Scene_h
#define Scene_h

#include <SFML/Graphics.hpp>
#include "Layoutable.h"

class Scene :
  public sf::Drawable,
  public Layoutable {};

#endif /* Scene_h */
