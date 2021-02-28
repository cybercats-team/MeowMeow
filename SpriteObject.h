//
// Created by cyberneticist on 27.01.21.
//

#ifndef MEOWMEOW_SPRITEOBJECT_H
#define MEOWMEOW_SPRITEOBJECT_H

#include <SFML/Graphics.hpp>

#include "TypeDefs.h"
#include "Debug.h"

class SpriteObject :
  private Dimensions,
  private SpriteInfo,
  public sf::Drawable
{
  private:
    sf::Sprite sprite;
    std::vector<sf::IntRect> frames;
    unsigned int currentFrame = 0;

    void setFrameRect(unsigned int frame);

    friend class SpriteSet;
  public:
    SpriteObject();
    SpriteObject(const sf::Texture& texture, const Dimensions& size, const SpriteInfo& info, const std::vector<sf::IntRect>& frames);
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    void setFrame(unsigned int frame);
    void nextFrame();
    [[nodiscard]] unsigned int getWidth() const;
    [[nodiscard]] unsigned int getHeight() const;
    [[nodiscard]] bool isAnimated() const;
    [[nodiscard]] unsigned int getAnimationDuration() const;
    [[nodiscard]] unsigned int getFramesCount() const;
};

#endif //MEOWMEOW_SPRITEOBJECT_H
