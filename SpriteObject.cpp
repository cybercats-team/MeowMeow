//
// Created by cyberneticist on 27.01.21.
//

#include "SpriteObject.h"

SpriteObject &SpriteObject::operator<<(const SpriteSize& size) {
  width = size.width;
  height = size.height;

  return *this;
}

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
}

void SpriteObject::draw(sf::RenderTarget &target, sf::RenderStates states) const {
  target.draw(sprite, states);
}

void SpriteObject::setFrameRect(unsigned int frame) {
  sprite.setTextureRect(frames[frame]);
}