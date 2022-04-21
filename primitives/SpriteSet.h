//
// Created by cyberneticist on 25.01.21.
//

#ifndef SpriteSet_h
#define SpriteSet_h

#include <SFML/Graphics.hpp>

#include "SpriteObject.h"

using Rectangle = struct Rectangle
  : public Dimensions 
{
  unsigned int left = 0;
  unsigned int top = 0;
};

using SpriteFrame = struct SpriteFrame {
  Rectangle rect{};
  Rectangle rect2k{};
  Rectangle rect4k{};
};

class SpriteSet {
  private:
    unsigned int spritesCount = 0;
    sf::Texture texture{};
    Dimensions spriteSize{};
    std::vector<SpriteInfo> sprites{};
    std::vector<std::vector<Rectangle>> frames{};

    void fillFrames(std::vector<sf::IntRect>& targetFrames, unsigned int spriteIndex);

    friend class SpriteManager;
  public:
    [[nodiscard]] unsigned int getSpritesCount() const;
    [[nodiscard]] unsigned int getSpriteWidth() const;
    [[nodiscard]] unsigned int getSpriteHeight() const;
    SpriteObject getSprite(unsigned int index);
    void getSprite(SpriteObject& spriteObject, unsigned int index);
};

#endif //SpriteSet_h
