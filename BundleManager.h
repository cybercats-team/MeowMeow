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
    Screen& screen;
    ResourceManager& resourceManager;
  
    template<typename T>
    T screenQuery(T value, T value2k, T value4k) const {
      switch (screen.getScale()) {
        case ScreenScale::RetinaOr2K:
          return value2k;
        case ScreenScale::UltraHD:
          return value4k;
        default:
          return value;
      }
    }
  public:
    BundleManager(ResourceManager& resourceManager, Screen& screen) :
      screen(screen),
      resourceManager(resourceManager) {}
    virtual bool initialize() = 0;
};

#endif /* BundleManager_h */
