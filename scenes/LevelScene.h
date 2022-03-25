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
#include "../utils/Math.h"
#include "../Debug.h"

class LevelScene : public Scene {
  private:
    LevelMap& map;
    std::vector<AnimationState> animated;
    sf::Int64 maxFrameInterval;
    sf::Clock animateTimer;

    void pushAnimatable(Animatable& sprite);
    void onAnimate();
    void onMapLoaded();

    friend class LevelController;
  public:
    explicit LevelScene(LevelMap& map);
    void onPresented() override;
    void onBeforeRender() override;
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    void layout(const Screen& screen) override;
};

#endif /* LevelScene_h */
