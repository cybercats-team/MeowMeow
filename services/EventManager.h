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

#include "../interfaces/Initializable.h"
#include "StateManager.h"

class EventManager : public Initializable {
  private:
    sf::Window& source;
    StateManager& stateManager;
  
    bool processSystemEvents(sf::Event& event);
  public:
    EventManager(sf::Window& source, StateManager& stateManager);
    void processEvents();
    bool initialize() override;
};

#endif /* EventManager_hpp */
