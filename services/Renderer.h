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
#include "../interfaces/BundleManager.h"

#include "../primitives/Screen.h"
#include "../utils/Debug.h"

class Renderer : public BundleManager {
  private:
    sf::RenderWindow& window;
    std::string windowTitle;
    Renderable& subject;
  
  public:
    Renderer(
      ResourceManager& resourceManager,
      Screen& screen,
      sf::RenderWindow& window,
      std::string windowTitle,
      Renderable& subject
    );
  
    bool initialize() override;
    void render();
};

#endif /* Renderer_hpp */
