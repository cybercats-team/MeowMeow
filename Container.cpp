//
//  SceneContainer.cpp
//  MeowMeow
//
//  Created by Alex Serdukov on 11.04.2021.
//  Copyright © 2021 Alex Serdukov. All rights reserved.
//

#include "Container.h"

Container::Container(Screen& screen, ResourceManager& resourceManager) :
  screen(screen), resourceManager(resourceManager),
  spriteManager(resourceManager, screen),
  levelManager(spriteManager, resourceManager, screen) {}

bool Container::initialize() {
  return spriteManager.initialize() && levelManager.initialize();
}
