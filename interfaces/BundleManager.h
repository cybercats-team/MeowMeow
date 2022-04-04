//
//  BundleManager.h
//  MeowMeow
//
//  Created by Alex Serdukov on 16.02.2021.
//  Copyright © 2021 Alex Serdukov. All rights reserved.
//

#ifndef BundleManager_h
#define BundleManager_h

#include "../interfaces/Initializable.h"
#include "../primitives/Screen.h"
#include "../services/ResourceManager.h"

class BundleManager : public Initializable {
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
};

#endif /* BundleManager_h */
