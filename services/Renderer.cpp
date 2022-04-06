//
//  Renderer.cpp
//  MeowMeow
//
//  Created by Alex Serdukov on 06.04.2022.
//  Copyright © 2022 Alex Serdukov. All rights reserved.
//

#include "Renderer.h"

Renderer::Renderer(Renderable& subject, sf::RenderWindow& target) :
  subject(subject), target(target) {}

void Renderer::render() {
  target.clear();
  subject.onBeforeRender();
  
  // Draw the scenes
  target.draw(subject);
  // Update the window
  target.display();
}
