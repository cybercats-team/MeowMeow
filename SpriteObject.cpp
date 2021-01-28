//
// Created by cyberneticist on 27.01.21.
//

#include "SpriteObject.h"

SpriteObject::SpriteObject() : sf::Transformable(), SpriteSize({}), SpriteInfo({}), frames({}), sprite() {}

SpriteObject::SpriteObject(const sf::Texture& texture, const SpriteSize& size, const SpriteInfo& info, const std::vector<sf::IntRect>& frames)
  : sf::Transformable(), SpriteSize(size), SpriteInfo(info), frames(std::move(frames)), sprite(texture) {};

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
  sprite.setTextureRect(frames[frame]);
}
