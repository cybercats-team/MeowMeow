//
//  SceneController.cpp
//  MeowMeow
//
//  Created by Alex Serdukov on 18.10.2021.
//  Copyright © 2021 Alex Serdukov. All rights reserved.
//

#include "SceneController.h"

SceneController::SceneController(Application& app) :
  app(app), focusedScene(-1), scenes({}) {}

bool SceneController::initialize() {
  return true;
}

void SceneController::onDisposed() {
  removeAll();
}

void SceneController::present(Scene& scene) {
  pushScene(scene);
  focusTop();
}

void SceneController::pushScene(Scene& scene) {
  const Screen& screen = app.getScreen();
  
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

void SceneController::remove(Scene& scene) {
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

void SceneController::focus(Scene& scene) {
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

void SceneController::onBeforeEvents() {
  if (hasFocused()) {
    getFocused().onBeforeEvents();
  }
}

void SceneController::onAction(Action& action) {
  if (hasFocused()) {
    getFocused().onAction(action);
  }
}

void SceneController::onEvent(sf::Event& event) {
  if (hasFocused()) {
    getFocused().onEvent(event);
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
    getFocused().onBlurred();
    focusedScene = -1;
  }
}
