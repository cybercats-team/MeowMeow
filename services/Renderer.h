//
//  Renderer.hpp
//  MeowMeow
//
//  Created by Alex Serdukov on 06.04.2022.
//  Copyright © 2022 Alex Serdukov. All rights reserved.
//

#ifndef Renderer_hpp
#define Renderer_hpp

#include <SFML/Graphics.hpp>
#include <functional>
#include <string>

#include "../interfaces/Renderable.h"
#include "../interfaces/Initializable.h"
#include "../interfaces/ForwardDecl.h"

#include "../primitives/Screen.h"
#include "../services/ResourceManager.h"
#include "../services/SettingsManager.h"

#include "../utils/Debug.h"

class Renderer : public Initializable {
  private:
    const Screen& screen;
    ResourceManager& resourceManager;
    sf::RenderWindow& window;
    SettingsManager& settingsManager;
    Renderable& subject;
  
  public:
    explicit Renderer(Application& app);
  
    bool initialize() override;
    void render();
};

#endif /* Renderer_hpp */
