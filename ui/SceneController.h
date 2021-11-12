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

#include "../AppState.h"

#include "../interfaces/Controller.h"
#include "../interfaces/Scene.h"

#include "../utils/Array.h"

class SceneController : public Controller {
  private:
    [[maybe_unused]] AppState& appState;
    Container& container;
    Screen& screen;

    std::vector<std::reference_wrapper<Scene>> scenes;
    long focusedScene;
  
    void clearFocused();
  public:
    explicit SceneController(AppState& appState);
    bool loadResources() override;
    ~SceneController() override;
    
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
  
    void onEvent(sf::Event& event) override;
  
    void onBeforeRender() override;
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};

#endif /* SceneController_h */
