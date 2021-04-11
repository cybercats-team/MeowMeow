//
//  Animatable.h
//  MeowMeow
//
//  Created by Alex Serdukov on 11.04.2021.
//  Copyright © 2021 Alex Serdukov. All rights reserved.
//

#ifndef Animatable_h
#define Animatable_h

#include <SFML/System.hpp>

class Animatable {
  public:
    virtual void setFrame(unsigned int frame) = 0;
    virtual void nextFrame() = 0;
    virtual bool isAnimated() const = 0;
    virtual unsigned int getAnimationDuration() const = 0;
    virtual unsigned int getFramesCount() const = 0;
};

typedef struct AnimationState {
  const Animatable& animatable;
  const sf::Int64 frameInterval;
  sf::Int64 lastFrame;
  
  AnimationState(Animatable& animatable) :
    lastFrame(0),
    animatable(animatable),
    frameInterval((sf::Int64) (1000.0 * (
      (float) animatable.getAnimationDuration() /
      (float) animatable.getFramesCount()
    ))) {}
} AnimationState;

#endif /* Animatable_h */
