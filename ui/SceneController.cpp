//
//  SceneController.cpp
//  MeowMeow
//
//  Created by Alex Serdukov on 18.10.2021.
//  Copyright © 2021 Alex Serdukov. All rights reserved.
//

#include "SceneController.h"

SceneController::SceneController(Application& app) :
  app(app), focusedScene(nullptr), scenes({}) {}

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
  using namespace std;

  if (!Array::includes(scenes, scene)) {
    return;
  }

  if (hasFocused()) {
    Scene& focused = getFocused();

    if (addressof(focused) == addressof(scene)) {
      clearFocused();
    }
  }

  scene.onDisposed();
  Array::remove(scenes, scene);

  if (!hasFocused()) {
    focusTop();
  }
}

void SceneController::focusTop() {
  if (scenes.empty()) {
    return;
  }

  focus((Scene&) scenes.back());
}

void SceneController::focus(Scene& scene) {
  using namespace std;

  if (!Array::includes(scenes, scene)) {
    return;
  }

  unique_ptr<Scene> scenePtr(addressof(scene));
  clearFocused();

  focusedScene = move(scenePtr);
  scene.onFocused();
}

bool SceneController::hasFocused() const {
  return focusedScene.get() != nullptr;
}

Scene& SceneController::getFocused() {
  return *(focusedScene.get());
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

    focusedScene.release();
    focusedScene = nullptr;
  }
}
