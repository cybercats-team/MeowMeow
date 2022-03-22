//
//  LevelScene.cpp
//  MeowMeow
//
//  Created by Alex Serdukov on 08.04.2021.
//  Copyright © 2021 Alex Serdukov. All rights reserved.
//

#include "LevelScene.h"

LevelScene::LevelScene(LevelMap& map) :
  map(map),
  maxFrameInterval(0),
  animated({}),
  animateTimer()
{
  onMapLoaded();
}

void LevelScene::onPresented() {
  animateTimer.restart();
}

void LevelScene::layout(const Screen& screen) {
  map.layout(screen);
}

void LevelScene::onBeforeRender() {
  onAnimate();
}

void LevelScene::onMapLoaded() {
  for (auto& sprite: map.sprites) {
    if (sprite.isAnimated()) {
      pushAnimatable(sprite);
    }
  }
}

void LevelScene::onAnimate() {
  using namespace sf;
  
  Int64 elapsedTime = animateTimer.getElapsedTime().asMicroseconds();
  bool animationFinished = elapsedTime >= maxFrameInterval;
  
  for (auto& state: animated) {
    if ((elapsedTime - state.lastFrame) >= state.frameInterval) {
      state.lastFrame = animationFinished ? 0 : elapsedTime;
      state.animatable.nextFrame();
    }
  }
  
  if (animationFinished) {
    animateTimer.restart();
  }
}

void LevelScene::draw(sf::RenderTarget& target, sf::RenderStates states) const {
  map.draw(target, states);
}

void LevelScene::pushAnimatable(Animatable& sprite) {
  AnimationState state(sprite);
  animated.push_back(state);
  
  if (maxFrameInterval == 0) {
    maxFrameInterval = state.frameInterval;
    return;
  }
  
  maxFrameInterval = Math::lcm(maxFrameInterval, state.frameInterval);
}
