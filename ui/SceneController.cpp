//
//  SceneController.cpp
//  MeowMeow
//
//  Created by Alex Serdukov on 18.10.2021.
//  Copyright © 2021 Alex Serdukov. All rights reserved.
//

#include "SceneController.h"

SceneController::SceneController(AppState& appState) :
  appState(appState),
  container(appState.container),
  screen(container.screen),
  focusedScene(-1),
  scenes({}) {}

SceneController::~SceneController() {
  removeAll();
}

bool SceneController::loadResources() {
  return true;
}

[[maybe_unused]] void SceneController::present(Scene& scene) {
  pushScene(scene);
  focusTop();
}

void SceneController::pushScene(Scene& scene) {
  scenes.emplace_back(scene);
  
  scene.onPresented();
  scene.layout(screen);
}

void SceneController::removeAll() {
  clearFocused();
  
  for (Scene& scene: scenes) {
    scene.onDisposed();
  }
  
  scenes.clear();
}

[[maybe_unused]] void SceneController::remove(Scene& scene) {
  long sceneIndex = Array::indexOf(scenes, scene);
  
  if (sceneIndex >= 0) {
    remove(sceneIndex);
  }
}

void SceneController::remove(long sceneIndex) {
  if (sceneIndex >= scenes.size()) {
    return;
  }
  
  Scene& scene = scenes[sceneIndex];
  
  if (hasFocused() && (sceneIndex == focusedScene)) {
    clearFocused();
  }
  
  scene.onDisposed();
  Array::remove(scenes, sceneIndex);
  
  if (!hasFocused()) {
    focusTop();
  }
}

void SceneController::focusTop() {
  unsigned long scenesCount = scenes.size();
  
  if (scenesCount > 0) {
    focus((long) (scenesCount - 1));
  }
}

[[maybe_unused]] void SceneController::focus(Scene& scene) {
  long sceneIndex = Array::indexOf(scenes, scene);
  
  if (sceneIndex >= 0) {
    focus(sceneIndex);
  }
}

void SceneController::focus(long sceneIndex) {
  clearFocused();
  
  if (sceneIndex < scenes.size()) {
    Scene& scene = scenes[sceneIndex];
    
    focusedScene = sceneIndex;
    scene.onFocused();
  }
}

bool SceneController::hasFocused() const {
  return focusedScene >= 0;
}

Scene& SceneController::getFocused() {
  return scenes[focusedScene];
}

void SceneController::onEvent(sf::Event& event) {
  // TODO: filter key-events only ?
  if (hasFocused()) {
    Scene& focused = getFocused();
    
    focused.onEvent(event);
  }
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

void SceneController::clearFocused() {
  if (hasFocused()) {
    Scene& focused = getFocused();
    
    focused.onBlurred();
    focusedScene = -1;
  }
}
