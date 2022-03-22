//
// Created by cyberneticist on 24.02.21.
//

#include "LevelMap.h"

#include <cmath>

LevelMap::LevelMap():
  AggregatedMapInfo(),
  sprites(),
  tiles(),
  tileSprites(),
  newLine(),
  nextCol(),
  nextRow(),
  mapView(),
  borderView(),
  screenView(),
  nextBorderRow(),
  nextBorderCol(),
  borderColHeight(0) {}

void LevelMap::layout(const Screen& screen) {
  screenView.width = (float) screen.getWidth();
  screenView.height = (float) screen.getHeight();
  newLine.y = (float) tileSize.height;
    
  layoutMap();
  layoutBorder();
}

void LevelMap::draw(sf::RenderTarget &target, sf::RenderStates states) const {
  using namespace sf;
  using namespace std;
  
  drawMap(target, states);
  drawBorders(target, states);
  drawSideBorders(target, states);
}

void LevelMap::layoutMap() {
  using namespace std;

  const auto tileWidth = (float) tileSize.width;
  
  mapView.width = (float) width * tileWidth;
  mapView.height = (float) height * (float) tileSize.height;
  mapView.left = floor((screenView.width - mapView.width) / 2);
  mapView.top = floor((screenView.height - mapView.height) / 2);
  
  nextCol.x = tileWidth;
  nextRow.x = - mapView.width;
  nextRow.y = newLine.y;
}

void LevelMap::layoutBorder() {
  using namespace std;

  const auto tileWidth = (float) tileSize.width;
  const auto tileHeight = (float) tileSize.height;
  
  borderView.width = ceil(mapView.left / tileWidth);
  borderView.height = ceil(mapView.top / tileHeight);
  borderView.left = mapView.left - borderView.width * tileWidth;
  borderView.top = mapView.top - borderView.height * tileHeight;
  borderColHeight = mapView.top + mapView.height;
  
  nextBorderRow.x = 2 * borderView.left - screenView.width;
  nextBorderRow.y = newLine.y;
  nextBorderCol.x = nextCol.x;
  nextBorderCol.y = - mapView.height;
}

void LevelMap::drawMap(sf::RenderTarget &target, sf::RenderStates states) const {
  using namespace sf;
  
  Transformable position{};
  position.setPosition(mapView.left, mapView.top);

  for (unsigned int row = 0; row < height; row++) {
    for (unsigned int col = 0; col < width; col++) {
      for (auto spriteIndex: tileSprites[row][col]) {
        const SpriteObject& sprite = sprites[spriteIndex];
                
        target.draw(sprite, position.getTransform());
      }
    
      position.move(nextCol);
    }
    
    position.move(nextRow);
  }
}

void LevelMap::drawBorders(sf::RenderTarget &target, sf::RenderStates states) const {
  using namespace sf;
  using namespace std;

  const auto maxRow = (unsigned int) borderView.height;
  const SpriteObject& border = sprites[borderTile];
  vector<Transformable> positions = { Transformable(), Transformable() };
  
  positions[0].setPosition(borderView.left, borderView.top);
  positions[1].setPosition(borderView.left, mapView.top + mapView.height);
  
  for (unsigned int borderRow = 0; borderRow < maxRow; borderRow++) {
    while (positions[0].getPosition().x < screenView.width) {
      for (auto& position: positions) {
        target.draw(border, position.getTransform());
        position.move(nextCol);
      }
    }
    
    for (auto& position: positions) position.move(nextBorderRow);
  }
}

void LevelMap::drawSideBorders(sf::RenderTarget &target, sf::RenderStates states) const {
  using namespace sf;
  using namespace std;

  const auto maxCol = (unsigned int) borderView.width;
  const SpriteObject& border = sprites[borderTile];
  vector<Transformable> positions = { Transformable(), Transformable() };
  
  positions[0].setPosition(borderView.left, mapView.top);
  positions[1].setPosition(mapView.left + mapView.width, mapView.top);
  
  for (unsigned int borderCol = 0; borderCol < maxCol; borderCol++) {
    while (positions[0].getPosition().y < borderColHeight) {
      for (auto& position: positions) {
        target.draw(border, position.getTransform());
        position.move(newLine);
      }
    }
    
    for (auto& position: positions) position.move(nextBorderCol);
  }
}
