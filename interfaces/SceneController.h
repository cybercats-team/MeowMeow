//
//  SceneController.hpp
//  MeowMeow
//
//  Created by Alex Serdukov on 18.10.2021.
//  Copyright © 2021 Alex Serdukov. All rights reserved.
//

#ifndef SceneController_h
#define SceneController_h

#include <vector>
#include <functional>

#include <SFML/Graphics.hpp>
#include "EventHandler.h"

#include "../AppState.h"
#include "Scene.h"

#include "../utils/Array.h"

class SceneController :
  public sf::Drawable,
  public EventHandler,
  public Disposable
{
  private:
    [[maybe_unused]] AppState& appState;
    Container& container;
    Screen& screen;

    std::vector<std::reference_wrapper<Scene>> scenes;
    long focusedScene;
  
    void clearFocused();
  public:
    explicit SceneController(AppState& appState);
    
    void present(Scene& scene);
    void pushScene(Scene& scene);

    void removeAll();
    [[maybe_unused]] void remove(Scene& scene);
    void remove(long sceneIndex);
    
    void focusTop();
    void focus(long sceneIndex);
    [[maybe_unused]] void focus(Scene& scene);

    [[nodiscard]] bool hasFocused() const;
    Scene& getFocused();
  
    void onBeforeEvent() override;
    void onEvent(sf::Event& event) override;
  
    void onBeforeRender() override;
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    void onDisposed() override;
};

#endif /* SceneController_h */
