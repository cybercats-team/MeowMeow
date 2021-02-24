//
// Created by cyberneticist on 24.02.21.
//

#ifndef MEOWMEOW_LEVELMAP_H
#define MEOWMEOW_LEVELMAP_H

#include <vector>
#include <SFML/Graphics.hpp>

#include "TypeDefs.h"
#include "SpriteObject.h"

class LevelMap :
  private AggregatedMapInfo,
  public sf::Drawable
{
  private:
    std::vector<SpriteObject> sprites;
    std::vector<std::vector<TileInfo>> tiles;
    std::vector<std::vector<std::vector<unsigned int>>> tileSprites;

    friend class LevelManager;
  public:
    LevelMap();
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};


#endif //MEOWMEOW_LEVELMAP_H
