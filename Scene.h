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
  public Layoutable
{
  public:
    void layout(Screen& screen) override {}
    virtual void onMount() {}
    virtual void onBeforeEvent() {}
    virtual void onEvent(sf::Event& event) {}
    virtual void onBeforeRender() {}
};

#endif /* Scene_h */
