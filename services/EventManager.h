//
//  EventManager.hpp
//  MeowMeow
//
//  Created by Alex Serdukov on 06.04.2022.
//  Copyright © 2022 Alex Serdukov. All rights reserved.
//

#ifndef EventManager_hpp
#define EventManager_hpp

#include <SFML/Window.hpp>
#include <vector>
#include <map>

#include "SettingsManager.h"
#include "StateManager.h"

using ActionMapping = struct ActionMapping {
  ActionType action;
  BindingData data{};
};

using ButtonAction = struct ButtonAction {
  sf::Event::EventType event; 
  ActionEventType action;
};

using ButtonMapping = struct AggregatedActionMapping {
  BindingType bindingType;
  ActionEventType actionType;
  std::vector<ActionMapping> bindings{};
};

class EventManager : public SettingsListener
{
  private:
    sf::Window& source;
    StateManager& stateManager;
    ActionsBindings bindings;
    std::map<sf::Event::EventType, ButtonMapping> buttonsMapping;

    bool processSystemEvents(sf::Event& event);
    bool processActionEvents(sf::Event& event, Action& action);
    bool processButtonEvents(sf::Event& event, Action& action);
    bool processJoystickEvents(sf::Event& event, Action& action);
    bool processMouseEvents(sf::Event& event, Action& action);

    static const std::map<BindingType, std::vector<ButtonAction>> buttonActions;
  public:  
    EventManager(sf::Window& source, StateManager& stateManager, SettingsManager& settingsManager);
    void onSettingsUpdated(const Settings& settings) override;
    void processEvents();
};

#endif /* EventManager_hpp */
