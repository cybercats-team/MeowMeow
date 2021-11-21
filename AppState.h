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
  
    bool setActiveController(Controller* controller);
    bool initializeController(Controller& controller);
    void disposeController();

    friend class SceneController;
  public:
    explicit AppState(Container& container);
    ~AppState();

    bool initialize();
    Controller& getActiveController();
  
    bool showSplash();
    bool loadLevel(unsigned int realmId, unsigned int levelId);
};

#endif /* AppState_h */
