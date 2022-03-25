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

#include "../Container.h"

#include "../interfaces/Controller.h"
#include "../interfaces/Scene.h"

#include "../utils/Array.h"
#include "../Debug.h"

class SceneController : public Controller {
  private:
    std::vector<std::reference_wrapper<Scene>> scenes;
    long focusedScene;
    void clearFocused();

  protected:
    Container& container;
    const Screen& screen;

    void present(Scene& scene);
    void pushScene(Scene& scene);

    void removeAll();
    void remove(Scene& scene);
    void remove(long sceneIndex);

    void focusTop();
    void focus(long sceneIndex);
    void focus(Scene& scene);

    bool hasFocused() const;
    Scene& getFocused();

  public:
    explicit SceneController(Container& container);
    bool loadResources() override;
    void onDisposed() override;

    void onEvent(sf::Event& event) override;
    void onBeforeRender() override;
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};

#endif /* SceneController_h */
