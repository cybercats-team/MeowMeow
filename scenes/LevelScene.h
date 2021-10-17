//
//  LevelScene.hpp
//  MeowMeow
//
//  Created by Alex Serdukov on 08.04.2021.
//  Copyright © 2021 Alex Serdukov. All rights reserved.
//

#ifndef LevelScene_h
#define LevelScene_h

#include <SFML/System.hpp>

#include "../interfaces/Scene.h"
#include "../primitives/LevelMap.h"
#include "../Utils.h"

class LevelScene : public Scene {
  private:
    LevelMap& map;
    std::vector<AnimationState> animated;
    sf::Int64 maxFrameInterval;
    sf::Clock animateTimer;
  
    void pushAnimatable(Animatable& sprite);
    void onAnimate();
  public:
    LevelScene(LevelMap& map);
    void onMount() override;
    void onBeforeRender() override;
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    void layout(Screen& screen) override;
};

#endif /* LevelScene_h */
