//
//  Presentable.h
//  MeowMeow
//
//  Created by Alex Serdukov on 18.10.2021.
//  Copyright © 2021 Alex Serdukov. All rights reserved.
//

#ifndef Presentable_h
#define Presentable_h

#include "EventHandler.h"
#include "Disposable.h"

class Presentable :
  public EventHandler,
  public Disposable
{
  public:
    virtual void onPresented() = 0;
    virtual void onFocused() = 0;
    virtual void onBlurred() = 0;    
};

#endif /* Presentable_h */
