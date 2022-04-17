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

#include "../interfaces/TypeDefs.h"

#include "SettingsManager.h"
#include "StateManager.h"

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
