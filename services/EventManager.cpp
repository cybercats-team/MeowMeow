//
//  EventManager.cpp
//  MeowMeow
//
//  Created by Alex Serdukov on 06.04.2022.
//  Copyright © 2022 Alex Serdukov. All rights reserved.
//

#include "EventManager.h"

const std::map<BindingType, std::vector<EventActionMapping>> EventManager::eventActionMappings = {
  { BindingType::Key, {
    { .event = sf::Event::EventType::KeyPressed, .action = ActionEventType::ActionPressed },
    { .event = sf::Event::EventType::KeyReleased, .action = ActionEventType::ActionReleased }
  }},
  { BindingType::MouseButton, {
    { .event = sf::Event::EventType::MouseButtonPressed, .action = ActionEventType::ActionPressed },
    { .event = sf::Event::EventType::MouseButtonReleased, .action = ActionEventType::ActionReleased }
  }},
  { BindingType::JoystickButton, {
    { .event = sf::Event::EventType::JoystickButtonPressed, .action = ActionEventType::ActionPressed },
    { .event = sf::Event::EventType::JoystickButtonReleased, .action = ActionEventType::ActionReleased }
  }},
  { BindingType::MouseMove, {
    { .event = sf::Event::EventType::MouseMoved, .action = ActionEventType::ActionStickMoved }
  }},
  { BindingType::JoystickMove, {
    { .event = sf::Event::EventType::JoystickMoved, .action = ActionEventType::ActionStickMoved }
  }}
};

EventManager::EventManager(sf::Window& source, StateManager& stateManager, SettingsManager& settingsManager) : 
  source(source), stateManager(stateManager), bindings(), mappings() 
{
  settingsManager.addListener(*this);
}

void EventManager::processEvents()
{
  sf::Event event{};

  stateManager.onBeforeEvents();

  while (source.pollEvent(event)) {
    if (processSystemEvents(event)) {
      break;
    }

    stateManager.onEvent(event);
  }
}

bool EventManager::processSystemEvents(sf::Event& event)
{
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

void EventManager::onSettingsUpdated(const Settings& settings)
{
  bindings = settings.bindings;
  //TODO: update binding map
}
