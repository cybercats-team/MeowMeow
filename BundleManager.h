//
//  BundleManager.h
//  MeowMeow
//
//  Created by Alex Serdukov on 16.02.2021.
//  Copyright © 2021 Alex Serdukov. All rights reserved.
//

#ifndef BundleManager_h
#define BundleManager_h

#include "Screen.h"
#include "ResourceManager.h"

class BundleManager {
  protected:
    ScreenScale screenScale;
    ResourceManager& resourceManager;
  public:
    BundleManager(ResourceManager& resourceManager, Screen& screen) :
      screenScale(screen.scale),
      resourceManager(resourceManager) {}
};

#endif /* BundleManager_h */
