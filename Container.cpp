//
//  SceneContainer.cpp
//  MeowMeow
//
//  Created by Alex Serdukov on 11.04.2021.
//  Copyright © 2021 Alex Serdukov. All rights reserved.
//

#include "Container.h"

Container::Container(Screen& screen) :
  screen(screen), scenes({}) {}

void Container::pushScene(Scene& scene) {
  scenes.push_back(scene);
  
  scene.onMount();
  scene.layout(screen);
}

void Container::onBeforeEvent() {
  for (Scene& scene: scenes) {
    scene.onBeforeEvent();
  }
}

void Container::onEvent(sf::Event& event) {
  for (Scene& scene: scenes) {
    scene.onEvent(event);
  }
}

void Container::onBeforeRender() {
  for (Scene& scene: scenes) {
    scene.onBeforeRender();
  }
}

void Container::draw(sf::RenderTarget& target, sf::RenderStates states) const {
  for (Scene& scene: scenes) {
    target.draw(scene);
  }
}
