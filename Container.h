//
//  SceneContainer.hpp
//  MeowMeow
//
//  Created by Alex Serdukov on 11.04.2021.
//  Copyright © 2021 Alex Serdukov. All rights reserved.
//

#ifndef Container_h
#define Container_h

#include <list>
#include <functional>

#include "Screen.h"
#include "Scene.h"

class Container : public Scene {
  private:
    Screen& screen;
    std::list<std::reference_wrapper<Scene>> scenes;
  
  public:
    Container(Screen& screen);
    void pushScene(Scene& scene);
  
    void onBeforeEvent() override;
    void onEvent(sf::Event& event) override;
    void onBeforeRender() override;
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};

#endif /* Container_h */
