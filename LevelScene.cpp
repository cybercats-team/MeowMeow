//
//  LevelScene.cpp
//  MeowMeow
//
//  Created by Alex Serdukov on 08.04.2021.
//  Copyright © 2021 Alex Serdukov. All rights reserved.
//

#include "LevelScene.h"

LevelScene::LevelScene(LevelMap& map) : map(std::move(map)) {}

void LevelScene::draw(sf::RenderTarget& target, sf::RenderStates states) const {
  map.draw(target, states);
}

void LevelScene::layout(Screen& screen) {
  map.layout(screen);
}
