//
//  EventHandler.h
//  MeowMeow
//
//  Created by Alex Serdukov on 31.10.2021.
//  Copyright © 2021 Alex Serdukov. All rights reserved.
//

#ifndef EventHandler_h
#define EventHandler_h

#include <SFML/Graphics.hpp>

class EventHandler
{
  public:
    virtual void onEvent(sf::Event& event) = 0;
    virtual void onBeforeRender() = 0;
};

#endif /* EventHandler_h */
