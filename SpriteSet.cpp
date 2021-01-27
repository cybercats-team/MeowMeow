//
// Created by cyberneticist on 25.01.21.
//

#include "SpriteSet.h"

unsigned int SpriteSet::getSpritesCount() const {
  return spritesCount;
}

void SpriteSet::getSprite(SpriteObject &spriteObject, unsigned int index) {
  using namespace std;

  SpriteInfo& info = sprites[index];
  vector<SpriteRect>& spriteFrames = frames[index];

  spriteObject.sprite.setTexture(texture);

  //spriteObject.width = spriteSize.width;

  spriteObject << spriteSize;

  //spriteObject.frames = spriteFrames;

  //copy(spriteFrames.begin(), spriteFrames.end(), back_inserter(spriteObject.frames));
}
