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
#include <SFML/Graphics.hpp>

#include "./interfaces/Controller.h"
#include "./interfaces/EventHandler.h"
#include "./interfaces/Disposable.h"

#include "primitives/Screen.h"

#include "services/ResourceManager.h"
#include "services/SpriteManager.h"
#include "services/LevelManager.h"

#include "Debug.h"

class Container :
  public sf::Drawable,
  public EventHandler,
  public Disposable
{
  private:
    Screen& screen;
    ResourceManager& resourceManager;
    SpriteManager spriteManager;
    LevelManager levelManager;
    std::unique_ptr<Controller> activeController;

    bool setActiveController(Controller* controller);
    void disposeActiveController();
  public:
    Container(Screen& screen, ResourceManager& resourceManager);
    bool initialize();
    void onDisposed() override;

    void onEvent(sf::Event& event) override;
    void onBeforeRender() override;
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    bool hasActiveController() const;
    Controller& getActiveController() const;
    const Screen& getScreen() const;
    const ResourceManager& getResourceManager() const;
    const SpriteManager& getSpriteManager() const;
    LevelManager& getLevelManager();

    bool showSplash();
    bool loadLevel(unsigned int realmId, unsigned int levelId);
};

#endif /* Container_h */
