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

#include "../interfaces/Renderable.h"

class Renderer {
  private:
    sf::RenderWindow& target;
    Renderable& subject;
  public:
    Renderer(Renderable& subject, sf::RenderWindow& target);
    void render();
};

#endif /* Renderer_hpp */
