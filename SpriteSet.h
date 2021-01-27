//
// Created by cyberneticist on 25.01.21.
//

#ifndef MEOWMEOW_SPRITESET_H
#define MEOWMEOW_SPRITESET_H

#include <SFML/Graphics.hpp>

#include "SpriteObject.h"

typedef struct SpriteRect: SpriteSize {
  unsigned int left = 0;
  unsigned int top = 0;
} SpriteRect;

class SpriteSet {
  private:
    unsigned int spritesCount = 0;
    sf::Texture texture{};
    SpriteSize spriteSize{};
    std::vector<SpriteInfo> sprites{};
    std::vector<std::vector<SpriteRect>> frames{};

    friend class SpriteManager;
  public:
    [[nodiscard]] unsigned int getSpritesCount() const;
    void getSprite(SpriteObject& spriteObject, unsigned int index);
};

#endif //MEOWMEOW_SPRITESET_H
