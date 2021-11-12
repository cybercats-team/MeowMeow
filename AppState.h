//
//  AppState.hpp
//  MeowMeow
//
//  Created by Alex Serdukov on 31.10.2021.
//  Copyright © 2021 Alex Serdukov. All rights reserved.
//

#ifndef AppState_h
#define AppState_h

#include <functional>

#include "Container.h"

#include "./interfaces/Controller.h"

class AppState {
  private:
    Container& container;
    std::reference_wrapper<Controller> activeController;

    friend class SceneController;
  public:
    explicit AppState(Container& container);
    ~AppState();

    Controller& getActiveController();
};

#endif /* AppState_h */
