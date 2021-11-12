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
#include "Presentable.h"

class Scene :
  public sf::Drawable,
  public Layoutable,
  public Presentable
{
  public:
    void layout(Screen& screen) override {}
    void onPresented() override {}
    void onFocused() override {}
    void onBlurred() override {}
    void onEvent(sf::Event& event) override {}
    void onBeforeRender() override {}
    void onDisposed() override {}
};

#endif /* Scene_h */
