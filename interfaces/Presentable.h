//
//  Presentable.h
//  MeowMeow
//
//  Created by Alex Serdukov on 18.10.2021.
//  Copyright © 2021 Alex Serdukov. All rights reserved.
//

#ifndef Presentable_h
#define Presentable_h

#include <SFML/Graphics.hpp>

class Presentable
{
  public:
    virtual void onPresented() = 0;
    virtual void onFocused() = 0;
    virtual void onBlurred() = 0;
    virtual void onBeforeEvent() = 0;
    virtual void onEvent(sf::Event& event) = 0;
    virtual void onBeforeRender() = 0;
};

#endif /* Presentable_h */
