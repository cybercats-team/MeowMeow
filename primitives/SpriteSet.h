//
// Created by cyberneticist on 25.01.21.
//

#ifndef SpriteSet_h
#define SpriteSet_h

#include <SFML/Graphics.hpp>

#include "../interfaces/TypeDefs.h"
#include "SpriteObject.h"

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
    [[maybe_unused]] [[nodiscard]] unsigned int getSpritesCount() const;
    [[maybe_unused]] [[nodiscard]] unsigned int getSpriteWidth() const;
    [[maybe_unused]] [[nodiscard]] unsigned int getSpriteHeight() const;
    [[maybe_unused]] SpriteObject getSprite(unsigned int index);
    void getSprite(SpriteObject& spriteObject, unsigned int index);
};

#endif //SpriteSet_h
