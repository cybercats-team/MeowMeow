//
// Created by cyberneticist on 25.01.21.
//

#include "SpriteSet.h"

unsigned int SpriteSet::getSpritesCount() const {
  return spritesCount;
}

const SpriteSetInfo& SpriteSet::getInfo() const {
  return info;
}

SpriteInfo& SpriteSet::getSprite(unsigned int index) const {
  return const_cast<SpriteInfo&>(sprites[index]);
}

SpriteFrame& SpriteSet::getFrame(unsigned int spriteIndex, unsigned int index) const {
  return const_cast<SpriteFrame&>(frames[spriteIndex][index]);
}
