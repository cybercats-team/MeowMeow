//
//  SceneController.cpp
//  MeowMeow
//
//  Created by Alex Serdukov on 18.10.2021.
//  Copyright © 2021 Alex Serdukov. All rights reserved.
//

#include "SceneController.h"

SceneController::SceneController(Application& app) :
  app(app), focusedScene(), scenes({}) {}

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

  if (focusedScene) {
    Scene& focused = getFocused();

    if (addressof(focused) == addressof(scene)) {
      clearFocused();
    }
  }

  scene.onDisposed();
  Array::remove(scenes, scene);

  if (!focusedScene) {
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
  if (!Array::includes(scenes, scene)) {
    return;
  }

  clearFocused();

  focusedScene = std::ref(scene);
  scene.onFocused();
}

Scene& SceneController::getFocused() {
  return (Scene&) focusedScene.value();
}

void SceneController::onBeforeEvents() {
  if (focusedScene) {
    getFocused().onBeforeEvents();
  }
}

void SceneController::onAction(Action& action) {
  if (focusedScene) {
    getFocused().onAction(action);
  }
}

void SceneController::onEvent(sf::Event& event) {
  if (focusedScene) {
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
  if (focusedScene) {
    getFocused().onBlurred();
    focusedScene.reset();
  }
}
