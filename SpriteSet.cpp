//
// Created by cyberneticist on 25.01.21.
//

#include "SpriteSet.h"

unsigned int SpriteSet::getSpritesCount() const {
  return spritesCount;
}

unsigned int SpriteSet::getSpriteWidth() const {
  return spriteSize.width;
}

unsigned int SpriteSet::getSpriteHeight() const {
  return spriteSize.height;
}

void SpriteSet::getSprite(SpriteObject &spriteObject, unsigned int index) {
  using namespace sf;
  using namespace std;

  SpriteInfo& info = sprites[index];
  vector<SpriteRect>& spriteFrames = frames[index];
  
  spriteObject << spriteSize << info;
  spriteObject.sprite.setTexture(texture);
  
  for (auto& frame: spriteFrames) {
    IntRect rect(frame.left, frame.top, frame.width, frame.height);
    
    spriteObject.frames.push_back(rect);
  }
  
  spriteObject.setFrameRect(0);
}
