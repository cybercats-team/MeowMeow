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
#include <functional>

#include "../interfaces/Initializable.h"
#include "../interfaces/TypeDefs.h"

#include "StateManager.h"
#include "SettingsManager.h"

class EventManager : public Initializable {
  private:
    sf::Window& source;
    StateManager& stateManager;
    SettingsManager& settingsManager;
    std::reference_wrapper<const ActionsBindings> bindings = std::ref(SettingsManager::defaultSettings.bindings);

    bool processSystemEvents(sf::Event& event);
    const ActionsBindings& getBindings();
  public:
    EventManager(sf::Window& source, StateManager& stateManager, SettingsManager& settingsManager);
    bool initialize() override;
    void processEvents();
};

#endif /* EventManager_hpp */
