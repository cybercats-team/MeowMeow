//
//  AppState.cpp
//  MeowMeow
//
//  Created by Alex Serdukov on 31.10.2021.
//  Copyright © 2021 Alex Serdukov. All rights reserved.
//

#include "AppState.h"

AppState::AppState(Container& container) :
  container(container),
  activeController(SplashController(container.screen)) {}
