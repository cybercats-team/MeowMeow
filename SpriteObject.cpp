//
// Created by cyberneticist on 27.01.21.
//

#include "SpriteObject.h"

unsigned int SpriteObject::getWidth() const {
  return width;
}

unsigned int SpriteObject::getHeight() const {
  return height;
}

bool SpriteObject::isAnimated() const {
  return animated;
}

unsigned int SpriteObject::getAnimationDuration() const {
  return animationDuration;
}

unsigned int SpriteObject::getFramesCount() const {
  return framesCount;
}

void SpriteObject::setFrame(unsigned int frame) {
  if (!animated || (frame == currentFrame)) {
    return;
  }

  setFrameRect(frame);
  currentFrame = frame;
}

void SpriteObject::nextFrame() {
  unsigned int next = currentFrame + 1;
  
  if (next > (framesCount - 1)) {
    next = 0;
  }
  
  setFrame(next);
}

void SpriteObject::draw(sf::RenderTarget &target, sf::RenderStates states) const {
  states.transform *= getTransform();
  target.draw(sprite, states);
}

void SpriteObject::setFrameRect(unsigned int frame) {
  //  debugPrint("set frame rect" + std::to_string(frame));
  sprite.setTextureRect(frames[frame]);
}

SpriteObject &SpriteObject::operator<<(const SpriteSize& size) {
  width = size.width;
  height = size.height;

  return *this;
}

SpriteObject &SpriteObject::operator<<(const SpriteInfo& info) {
  animated = info.animated;
  animationDuration = info.animationDuration;
  framesCount = info.framesCount;

  return *this;
}
