//
//  EventHandler.h
//  MeowMeow
//
//  Created by Alex Serdukov on 31.10.2021.
//  Copyright © 2021 Alex Serdukov. All rights reserved.
//

#ifndef EventHandler_h
#define EventHandler_h

#include <SFML/Window.hpp>
#include <variant>

#include "TypeDefs.h"

class Action {
  public:
    ActionEventType event;
    ActionType action;
    std::variant<StickMoveDetails> details;

    const sf::Event& originalEvent;

    Action(const sf::Event& originalEvent)
      : originalEvent(originalEvent), details() {}

    StickMoveDetails& getStickMoveDetails() {
      return std::get<StickMoveDetails>(details);
    }
};

class EventHandler
{
  public:
    virtual void onBeforeEvents() = 0;
    virtual void onAction(Action& action) = 0;
    virtual void onEvent(sf::Event& event) = 0;
    virtual void onBeforeRender() = 0;
};

#endif /* EventHandler_h */
