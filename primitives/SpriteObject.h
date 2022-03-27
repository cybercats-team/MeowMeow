//
// Created by cyberneticist on 27.01.21.
//

#ifndef SpriteObject_h
#define SpriteObject_h

#include <SFML/Graphics.hpp>

#include "../interfaces/Animatable.h"
#include "../interfaces/TypeDefs.h"
#include "../utils/Debug.h"

class SpriteObject :
  private Dimensions,
  private SpriteInfo,
  public sf::Drawable,
  public Animatable
{
  private:
    sf::Sprite sprite;
    std::vector<sf::IntRect> frames;
    unsigned int currentFrame = 0;

    void setFrameRect(unsigned int frame);

    friend class SpriteSet;
  public:
    SpriteObject();
    SpriteObject(const sf::Texture& texture, const Dimensions& size, const SpriteInfo& info, std::vector<sf::IntRect> frames);
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    void setFrame(unsigned int frame) override;
    void nextFrame() override;

    [[nodiscard]] unsigned int getWidth() const;
    [[nodiscard]] unsigned int getHeight() const;
    [[nodiscard]] bool isAnimated() const;
    [[nodiscard]] unsigned int getAnimationDuration() const override;
    [[nodiscard]] unsigned int getFramesCount() const override;
};

#endif //SpriteObject_h
