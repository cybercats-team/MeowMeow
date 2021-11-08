//
// Created by cyberneticist on 25.01.21.
//

#include "SpriteSet.h"

[[maybe_unused]] unsigned int SpriteSet::getSpritesCount() const {
  return spritesCount;
}

[[maybe_unused]] unsigned int SpriteSet::getSpriteWidth() const {
  return spriteSize.width;
}

[[maybe_unused]] unsigned int SpriteSet::getSpriteHeight() const {
  return spriteSize.height;
}

void SpriteSet::getSprite(SpriteObject &spriteObject, unsigned int index) {
  using namespace sf;
  using namespace std;

  SpriteInfo& info = sprites[index];
  spriteObject.sprite.setTexture(texture);
  
  spriteObject.width = spriteSize.width;
  spriteObject.height = spriteSize.height;
  spriteObject.animated = info.animated;
  spriteObject.framesCount = info.framesCount;
  spriteObject.animationDuration = info.animationDuration;
    
  fillFrames(spriteObject.frames, index);
  spriteObject.setFrameRect(0);
}

[[maybe_unused]] SpriteObject SpriteSet::getSprite(unsigned int index) {
  using namespace sf;
  using namespace std;
  
  SpriteInfo& info = sprites[index];
  vector<IntRect> spriteFrames{};
  
  fillFrames(spriteFrames, index);
  return SpriteObject(texture, spriteSize, info, spriteFrames);
}

void SpriteSet::fillFrames(std::vector<sf::IntRect>& targetFrames, unsigned int spriteIndex) {
  using namespace sf;
  using namespace std;
  
  vector<Rectangle>& sourceFrames = frames[spriteIndex];
  
  for (auto& frame: sourceFrames) {
    IntRect rect(frame.left, frame.top, frame.width, frame.height);
    
    targetFrames.push_back(rect);
  }
}
