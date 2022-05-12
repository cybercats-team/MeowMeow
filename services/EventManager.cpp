//
//  EventManager.cpp
//  MeowMeow
//
//  Created by Alex Serdukov on 06.04.2022.
//  Copyright © 2022 Alex Serdukov. All rights reserved.
//

#include "EventManager.h"

const std::map<BindingType, std::vector<ButtonAction>> EventManager::buttonActions = {
  { BindingType::Key, {
    { .event = sf::Event::KeyPressed, .action = ActionEventType::ActionPressed },
    { .event = sf::Event::KeyReleased, .action = ActionEventType::ActionReleased }
  }},
  { BindingType::MouseButton, {
    { .event = sf::Event::MouseButtonPressed, .action = ActionEventType::ActionPressed },
    { .event = sf::Event::MouseButtonReleased, .action = ActionEventType::ActionReleased }
  }},
  { BindingType::JoystickButton, {
    { .event = sf::Event::JoystickButtonPressed, .action = ActionEventType::ActionPressed },
    { .event = sf::Event::JoystickButtonReleased, .action = ActionEventType::ActionReleased }
  }}
};

EventManager::EventManager(sf::Window& source, StateManager& stateManager, SettingsManager& settingsManager) : 
  source(source), stateManager(stateManager), bindings(), buttonsMapping() 
{
  settingsManager.addListener(*this);
}

void EventManager::processEvents()
{
  sf::Event event{};
  Action action(event);

  stateManager.onBeforeEvents();

  while (source.pollEvent(event)) {
    if (processSystemEvents(event)) {
      continue;
    }
    
    if (processActionEvents(event, action)) {
      stateManager.onAction(action);
    }

    stateManager.onEvent(event);
  }
}

bool EventManager::processSystemEvents(sf::Event& event)
{
  using namespace sf;
  
  /*if (event.type == Event::JoystickMoved) {
    Debug::printf("Joystick axis: %d %f", event.joystickMove.axis, event.joystickMove.position);
  }*/

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

bool EventManager::processActionEvents(sf::Event& event, Action& action) 
{
  using EventType = sf::Event::EventType;
  
  switch (event.type) {
    case EventType::KeyPressed:
    case EventType::KeyReleased:
    case EventType::MouseButtonPressed:
    case EventType::MouseButtonReleased:
    case EventType::JoystickButtonPressed:
    case EventType::JoystickButtonReleased:
      return processButtonEvents(event, action);
    case EventType::JoystickMoved:
      return processJoystickEvents(event, action);
    case EventType::MouseMoved:
      return processMouseEvents(event, action);
    default:
      return false;
  }
}

bool EventManager::processButtonEvents(sf::Event& event, Action& action)
{
  return false;
}

bool EventManager::processJoystickEvents(sf::Event& event, Action& action)
{
  return false;
}
  
bool EventManager::processMouseEvents(sf::Event& event, Action& action) 
{
  return false;
}

void EventManager::onSettingsUpdated(const Settings& settings)
{
  bindings = settings.bindings;
  //TODO: update binding map
}
