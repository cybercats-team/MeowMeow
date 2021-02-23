//
// Created by cyberneticist on 24.02.21.
//

#ifndef MEOWMEOW_LEVELMAP_H
#define MEOWMEOW_LEVELMAP_H

#include <vector>

#include "TypeDefs.h"
#include "SpriteObject.h"

class LevelMap : public AggregatedMapInfo {
  private:
    std::vector<SpriteObject> sprites;
    std::vector<std::vector<TileInfo>> tiles;
    std::vector<std::vector<std::vector<unsigned int>>> tileSprites;

    friend class LevelManager;
  public:
    LevelMap();
};


#endif //MEOWMEOW_LEVELMAP_H
