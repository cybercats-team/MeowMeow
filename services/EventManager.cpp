//
//  EventManager.cpp
//  MeowMeow
//
//  Created by Alex Serdukov on 06.04.2022.
//  Copyright © 2022 Alex Serdukov. All rights reserved.
//

#include "EventManager.h"

EventManager::EventManager(sf::Window& source, StateManager& stateManager) :
  source(source), stateManager(stateManager) {}

bool EventManager::initialize() {
  return true;
}

void EventManager::processEvents() {
  sf::Event event{};
  
  stateManager.onBeforeEvents();
  
  while (source.pollEvent(event)) {
    if (processSystemEvents(event)) {
      break;
    }
    
    stateManager.onEvent(event);
  }
}

bool EventManager::processSystemEvents(sf::Event& event) {
  using namespace sf;
  
  if (
    // Close window: exit
    (event.type == Event::Closed) ||
    // Escape pressed: exit
    (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape)
  ) {
    stateManager.exitApp();
    return true;
  }
  
  return false;
}