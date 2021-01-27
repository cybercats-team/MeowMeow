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

std::string SpriteSet::getTexturePath() const {
  using namespace std;
  
  switch (scale) {
    case ScreenScale::RetinaOr2K:
      return string(info.path2k);
    case ScreenScale::UltraHD:
      return string(info.path4k);
    default:
      return string(info.path);
  }
}

const SpriteSize& SpriteSet::getSpriteSize() const {
  switch (scale) {
    case ScreenScale::RetinaOr2K:
      return info.spriteSize2k;
    case ScreenScale::UltraHD:
      return info.spriteSize4k;
    default:
      return info.spriteSize;
  }
}

const SpriteInfo& SpriteSet::getSpriteInfo(unsigned int index) const {
  return const_cast<SpriteInfo&>(sprites[index]);
}

const SpriteRect& SpriteSet::getFrameRect(unsigned int spriteIndex, unsigned int index) const {
  const SpriteInfo& spriteInfo = getSpriteInfo(spriteIndex);
  const SpriteFrame& frame = frames[spriteIndex][spriteInfo.animated ? index : 0];
  
  switch (scale) {
    case ScreenScale::RetinaOr2K:
      return frame.rect2k;
    case ScreenScale::UltraHD:
      return frame.rect4k;
    default:
      return frame.rect;
  }
}
