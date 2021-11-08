//
//  SplashController.hpp
//  MeowMeow
//
//  Created by Alex Serdukov on 18.10.2021.
//  Copyright © 2021 Alex Serdukov. All rights reserved.
//

#ifndef SplashController_h
#define SplashController_h

#include "../interfaces/SceneController.h"

class SplashController :
  public SceneController
{
  public:
    explicit SplashController(Screen& screen);
};

#endif /* SplashController_h */
