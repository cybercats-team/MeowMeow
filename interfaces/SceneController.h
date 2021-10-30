//
//  SceneController.hpp
//  MeowMeow
//
//  Created by Alex Serdukov on 18.10.2021.
//  Copyright © 2021 Alex Serdukov. All rights reserved.
//

#ifndef SceneController_h
#define SceneController_h

#include <list>
#include <functional>

#include <SFML/Graphics.hpp>
#include "Layoutable.h"
#include "Presentable.h"

#include "../primitives/Screen.h"
#include "Scene.h"

class SceneController :
  public sf::Drawable,
  public Layoutable,
  public Presentable
{
  private:
    Screen& screen;
    std::list<std::reference_wrapper<Scene>> scenes;
  
  public:
    SceneController(Screen& screen);
    void present(Scene& scene);
  
    void onBeforeEvent() override {};
    void onEvent(sf::Event& event) override {};
  
    void onBeforeRender() override;
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};

#endif /* SceneController_h */
