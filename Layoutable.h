//
//  Layoutable.h
//  MeowMeow
//
//  Created by Alex Serdukov on 08.04.2021.
//  Copyright © 2021 Alex Serdukov. All rights reserved.
//

#ifndef Layoutable_h
#define Layoutable_h

#include "Screen.h"

class Layoutable {
  public:
    virtual void layout(Screen& screen) = 0;
};

#endif /* Layoutable_h */
