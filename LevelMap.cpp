//
// Created by cyberneticist on 24.02.21.
//

#include "LevelMap.h"

LevelMap::LevelMap():
  AggregatedMapInfo(),
  sprites(),
  tiles(),
  tileSprites(),
  nextCol(),
  nextRow(),
  startPos(),
  borderSizes(),
  borderPos() {}

void LevelMap::layout(Screen& screen) {
  const unsigned int screenWidth = screen.getWidth();
  const unsigned int screenHeight = screen.getHeight();
  
  nextCol.x = (float) tileSize.width;
  nextRow.y = (float) tileSize.height;
  nextRow.x = - (float) width * nextCol.x;
  
  startPos.x = floor((screenWidth + nextRow.x) / 2);
  startPos.y = floor((screenHeight - (float) height * nextRow.y) / 2);
  
  borderSizes.x = (unsigned int) ceil(startPos.x / (float) tileSize.width);
  borderSizes.y = (unsigned int) ceil(startPos.y / (float) tileSize.height);
  borderPos.x = startPos.x - (float) borderSizes.x * (float) tileSize.width;
  borderPos.y = startPos.y - (float) borderSizes.y * (float) tileSize.height; 
}

void LevelMap::draw(sf::RenderTarget &target, sf::RenderStates states) const {
  using namespace sf;
  using namespace std;
  
  /*const Vector2f& screenSize = target.getView().getSize();
  const unsigned int screenWidth = (unsigned int) screenSize.x;
  const unsigned int screenHeight = (unsigned int) screenSize.y;*/
  
  Transformable position{};
  position.setPosition(startPos);

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
