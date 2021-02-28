//
// Created by cyberneticist on 24.02.21.
//

#ifndef MEOWMEOW_LEVELMAP_H
#define MEOWMEOW_LEVELMAP_H

#include <vector>
#include <cmath>
#include <SFML/Graphics.hpp>

#include "TypeDefs.h"
#include "SpriteObject.h"
#include "Screen.h"

class LevelMap :
  private AggregatedMapInfo,
  public sf::Drawable
{
  private:
    std::vector<SpriteObject> sprites;
    std::vector<std::vector<TileInfo>> tiles;
    std::vector<std::vector<std::vector<unsigned int>>> tileSprites;
  
    sf::Vector2f startPos;
    sf::Vector2f nextCol;
    sf::Vector2f nextRow;
    sf::Vector2i borderSizes;
    sf::Vector2f borderPos;

    friend class LevelManager;
  public:
    LevelMap();
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    void layout(Screen& screen);
};


#endif //MEOWMEOW_LEVELMAP_H
