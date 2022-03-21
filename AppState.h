//
//  AppState.hpp
//  MeowMeow
//
//  Created by Alex Serdukov on 31.10.2021.
//  Copyright © 2021 Alex Serdukov. All rights reserved.
//

#ifndef AppState_h
#define AppState_h

#include <memory>
#include <SFML/Graphics.hpp>

#include "Container.h"
#include "./interfaces/Controller.h"
#include "./interfaces/EventHandler.h"

#include "Debug.h"

class AppState :
  public sf::Drawable,
  public EventHandler
{
  private:
    Container& container;
    std::unique_ptr<Controller> activeController;

    bool setActiveController(Controller* controller);

    friend class SceneController;
  public:
    explicit AppState(Container& container);

    bool initialize();
    bool hasActiveController() const;
    Controller& getActiveController() const;

    void onEvent(sf::Event& event) override;
    void onBeforeRender() override;
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    bool showSplash();
    bool loadLevel(unsigned int realmId, unsigned int levelId);
};

#endif /* AppState_h */
