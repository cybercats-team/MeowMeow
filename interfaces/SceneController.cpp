//
//  SceneController.cpp
//  MeowMeow
//
//  Created by Alex Serdukov on 18.10.2021.
//  Copyright © 2021 Alex Serdukov. All rights reserved.
//

#include "SceneController.h"

SceneController::SceneController(Screen& screen) :
  screen(screen), scenes({}), focusedScene(-1) {}

void SceneController::present(Scene& scene) {
  pushScene(scene);
  focus(scenes.size() - 1);
}

void SceneController::pushScene(Scene& scene) {
  scenes.push_back(scene);
  
  scene.onPresented();
  scene.layout(screen);
}

void SceneController::focus(unsigned long sceneIndex) {
  
  if (hasFocused()) {
    Scene& focused = getFocused();
    
    focused.onBlurred();
  }
  
  if (sceneIndex < scenes.size()) {
    Scene& scene = scenes[sceneIndex];
    
    scene.onFocused();
  }
}

bool SceneController::hasFocused() {
  return focusedScene >= 0;
}

Scene& SceneController::getFocused() {
  return scenes[focusedScene];
}

void SceneController::onBeforeRender() {
  for (Scene& scene: scenes) {
    scene.onBeforeRender();
  }
}

void SceneController::draw(sf::RenderTarget& target, sf::RenderStates states) const {
  for (Scene& scene: scenes) {
    target.draw(scene);
  }
}
