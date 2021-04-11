//
//  Animatable.h
//  MeowMeow
//
//  Created by Alex Serdukov on 11.04.2021.
//  Copyright © 2021 Alex Serdukov. All rights reserved.
//

#ifndef Animatable_h
#define Animatable_h

class Animatable {
  public:
    virtual void setFrame(unsigned int frame) = 0;
    virtual void nextFrame() = 0;
    virtual bool isAnimated() const = 0;
    virtual unsigned int getAnimationDuration() const = 0;
    virtual unsigned int getFramesCount() const = 0;
};

#endif /* Animatable_h */
