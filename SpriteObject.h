//
// Created by cyberneticist on 27.01.21.
//

#ifndef MEOWMEOW_SPRITEOBJECT_H
#define MEOWMEOW_SPRITEOBJECT_H

#include <SFML/Graphics.hpp>

typedef struct SpriteSize {
  unsigned int width = 0;
  unsigned int height = 0;
} SpriteSize;

typedef struct SpriteInfo {
  bool animated = false;
  unsigned int animationDuration = 0;
  unsigned int framesCount = 1;
} SpriteInfo;

class SpriteObject :
  private SpriteSize,
  private SpriteInfo,
  public sf::Drawable
{
  void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};


#endif //MEOWMEOW_SPRITEOBJECT_H
