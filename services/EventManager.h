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

using EventActionMapping = struct EventActionMapping {
  sf::Event::EventType event; 
  ActionEventType action;
};

using AggregatedActionMapping = struct AggregatedActionMapping {
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
    std::map<sf::Event::EventType, AggregatedActionMapping> mappings;

    bool processSystemEvents(sf::Event& event);

    static const std::map<BindingType, std::vector<EventActionMapping>> eventActionMappings;
  public:  
    EventManager(sf::Window& source, StateManager& stateManager, SettingsManager& settingsManager);
    void onSettingsUpdated(const Settings& settings) override;
    void processEvents();
};

#endif /* EventManager_hpp */
