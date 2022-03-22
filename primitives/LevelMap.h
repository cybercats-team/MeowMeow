//
// Created by cyberneticist on 24.02.21.
//

#ifndef LevelMap_h
#define LevelMap_h

#include <vector>
#include <cmath>

#include <SFML/Graphics.hpp>
#include "../interfaces/Layoutable.h"

#include "../interfaces/TypeDefs.h"
#include "SpriteObject.h"
#include "Screen.h"

class LevelMap :
  private AggregatedMapInfo,
  public sf::Drawable,
  public Layoutable
{
  private:
    std::vector<SpriteObject> sprites;
    std::vector<std::vector<TileInfo>> tiles;
    std::vector<std::vector<std::vector<unsigned int>>> tileSprites;
  
    sf::FloatRect screenView;
    sf::FloatRect mapView;
    sf::FloatRect borderView;
    sf::Vector2f newLine;
    sf::Vector2f nextCol;
    sf::Vector2f nextRow;
    sf::Vector2f nextBorderRow;
    sf::Vector2f nextBorderCol;
    float borderColHeight;
  
    void layoutMap();
    void layoutBorder();
    void drawMap(sf::RenderTarget &target, sf::RenderStates states) const;
    void drawBorders(sf::RenderTarget &target, sf::RenderStates states) const;
    void drawSideBorders(sf::RenderTarget &target, sf::RenderStates states) const;

    friend class LevelManager;
    friend class LevelScene;
  public:
    LevelMap();
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    void layout(const Screen& screen) override;
};

#endif //LevelMap_h
