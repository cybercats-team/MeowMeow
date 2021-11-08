//
//  AppState.hpp
//  MeowMeow
//
//  Created by Alex Serdukov on 31.10.2021.
//  Copyright © 2021 Alex Serdukov. All rights reserved.
//

#ifndef AppState_h
#define AppState_h

#include "Container.h"
#include "./interfaces/SceneController.h"

#include "./controllers/SplashController.h"

class AppState {
  private:
    Container& container;
    SceneController activeController;

    friend class Application;
    friend class SceneController;
  public:
    explicit AppState(Container& container);
};

#endif /* AppState_h */
