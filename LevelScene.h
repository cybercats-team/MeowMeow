//
//  LevelScene.hpp
//  MeowMeow
//
//  Created by Alex Serdukov on 08.04.2021.
//  Copyright © 2021 Alex Serdukov. All rights reserved.
//

#ifndef LevelScene_h
#define LevelScene_h

#include "Scene.h"
#include "LevelMap.h"

class LevelScene : public Scene {
  private:
    LevelMap map{};
  public:
    LevelScene(LevelMap& map);
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    void layout(Screen& screen) override;
};

#endif /* LevelScene_h */
