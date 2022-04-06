//
//  SceneContainer.hpp
//  MeowMeow
//
//  Created by Alex Serdukov on 11.04.2021.
//  Copyright © 2021 Alex Serdukov. All rights reserved.
//

#ifndef Container_h
#define Container_h

#include <memory>

#include "../interfaces/Controller.h"
#include "../interfaces/Disposable.h"
#include "../interfaces/Initializable.h"
#include "../interfaces/Renderable.h"
#include "../interfaces/Platform.h"

#include "../primitives/Screen.h"

#include "../utils/Debug.h"

class Application;

class StateManager :
  public Renderable,
  public Disposable,
  public Initializable
{
  private:
    Application& app;
    std::unique_ptr<Controller> activeController;

    bool setActiveController(Controller* controller);
    void disposeActiveController();
  public:
    explicit StateManager(Application& app);
    bool initialize() override;
    void onDisposed() override;

    void onBeforeEvents() override;
    void onEvent(sf::Event& event) override;
    void onBeforeRender() override;
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    bool hasActiveController() const;
    Controller& getActiveController() const;

    bool showSplash();
    bool loadLevel(unsigned int realmId, unsigned int levelId);
    void exitApp();
};

#endif /* Container_h */
