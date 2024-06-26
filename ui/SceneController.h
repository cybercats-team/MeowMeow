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
#include <optional>
#include <functional>

#include "../Application.h"
#include "../interfaces/Controller.h"
#include "../interfaces/Scene.h"

#include "../utils/Array.h"
#include "../utils/Debug.h"


class SceneController : public Controller {
  private:
    std::vector<std::reference_wrapper<Scene>> scenes;
    std::optional<std::reference_wrapper<Scene>> focusedScene;

    void clearFocused();

  protected:
    Application& app;

    void present(Scene& scene);
    void pushScene(Scene& scene);

    void removeAll();
    void remove(Scene& scene);

    void focusTop();
    void focus(Scene& scene);

    Scene& getFocused();

  public:
    explicit SceneController(Application& app);
    bool initialize() override;
    void onDisposed() override;

    void onBeforeEvents() override;
    void onAction(Action& action) override;
    void onEvent(sf::Event& event) override;
    void onBeforeRender() override;
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};

#endif /* SceneController_h */
