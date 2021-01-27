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
  private:
    sf::Sprite sprite{};
    std::vector<sf::IntRect> frames{};
    unsigned int currentFrame = 0;

    void setFrameRect(unsigned int frame);
    SpriteObject& operator<<(const SpriteSize&);

    friend class SpriteSet;
  public:

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    void setFrame(unsigned int frame);
    [[nodiscard]] unsigned int getWidth() const;
    [[nodiscard]] unsigned int getHeight() const;
    [[nodiscard]] bool isAnimated() const;
    [[nodiscard]] unsigned int getAnimationDuration() const;
    [[nodiscard]] unsigned int getFramesCount() const;
};

#endif //MEOWMEOW_SPRITEOBJECT_H
