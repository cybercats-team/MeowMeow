//
//  LevelManager.cpp
//  MeowMeow
//
//  Created by Alex Serdukov on 16.02.2021.
//  Copyright © 2021 Alex Serdukov. All rights reserved.
//

#include "LevelManager.h"

LevelManager::LevelManager(SpriteManager& spriteManager, ResourceManager& resourceManager, Screen& screen):
  BundleManager(resourceManager, screen),
  spriteManager(spriteManager),
  realms({}),
  levels({}) {}

bool LevelManager::initialize() {
  using namespace std;
  
  ifstream listFile;
  BundleHeader header{};
  RealmInfo info{};
  
  debugPrint("Loading bundle " + bundlePath);
  
  if (!resourceManager.load(listFile, header, bundlePath)) {
    return false;
  }
  
  for (unsigned int realmId = 0; realmId < header.itemsCount; realmId++) {
    vector<LevelInfo> levelsList{};
    
    listFile.read((char *) &info, sizeof(info));
    
    for (unsigned int levelId = 0; levelId < info.levelsCount; levelId++) {
      LevelInfo levelInfo{};
      
      listFile.read((char *) &levelInfo, sizeof(levelInfo));
      levelsList.push_back(levelInfo);
      
      debugPrint("Added level " + string(levelInfo.path));
    }
    
    levels.push_back(levelsList);
    realms.push_back(info);
  }
  
  return true;
}

unsigned int LevelManager::getRealmsCount() {
  return realms.size();
}

void LevelManager::getRealm(LevelRealm& realm, unsigned int realmId) {
  using namespace std;
  
  RealmInfo& info = realms[realmId];
  
  realm.levelsCount = info.levelsCount;
  realm.realmName = string(info.realmName);
  
  realm.levelNames.clear();
  fillLevelNames(realm.levelNames, realmId);
}

LevelRealm LevelManager::getRealm(unsigned int realmId) {
  using namespace std;
  
  RealmInfo& info = realms[realmId];
  vector<string> levelNames;
  
  fillLevelNames(levelNames, realmId);
  
  return LevelRealm(string(info.realmName), info.levelsCount, levelNames);
}

bool LevelManager::load(LevelMap& levelMap, unsigned int realmId, unsigned int levelId) {
  using namespace std;
  
  if (realmId > levels.size()) {
    debugPrint("Realm #" + to_string(realmId) + "not exists");
    return false;
  }
  
  vector<LevelInfo>& realmLevels = levels[realmId];
  
  if (levelId > realmLevels.size()) {
    debugPrint("Level #" + to_string(realmId) + "." + to_string(levelId) + " not exists");
    return false;
  }
  
  ifstream levelFile;
  BundleHeader header {};
  string path(realmLevels[levelId].path);
  
  debugPrint("Loading bundle " + path);

  if (!resourceManager.load(levelFile, header, path)) {
    return false;
  }
  
  MapInfo info{};
  levelFile.read((char *) &info, sizeof(info));
  
  levelMap.width = info.width;
  levelMap.height = info.height;
  levelMap.tileSize = getTileSize(info);
  levelMap.borderTile = info.borderTile;
  
  if (!loadSprites(levelFile, levelMap, info.spriteRefsCount)) {
    return false;
  }
    
  loadTiles(levelFile, levelMap);
  levelFile.close();
  return true;
}

void LevelManager::fillLevelNames(std::vector<std::string>& levelNames, unsigned int realmId) {
  using namespace std;
  
  for (auto& levelInfo: levels[realmId]) {
    levelNames.emplace_back(levelInfo.levelName);
  }
}

Dimensions LevelManager::getTileSize(MapInfo &info) const {
  switch (screenScale) {
    case ScreenScale::RetinaOr2K:
      return info.tileSize2k;
    case ScreenScale::UltraHD:
      return info.tileSize4k;
    default:
      return info.tileSize;
  }
}

bool LevelManager::loadSprites(std::ifstream& levelFile, LevelMap& levelMap, unsigned int count) {
  using namespace std;
  
  levelMap.sprites.clear();
  
  map<ObjectType, map<unsigned int, SpriteSet>> spriteSets = {
    {ObjectType::Terrain, {}},
    {ObjectType::MobileObject, {}}
  };
  
  for (unsigned int spriteIndex = 0; spriteIndex < count; spriteIndex++) {
    SpriteRef ref{};
    levelFile.read((char *) &ref, sizeof(ref));
    
    SpriteObject sprite{};
    map<unsigned int, SpriteSet>& setsRef = spriteSets[ref.objectType];
    
    if (setsRef.count(ref.spriteSetIndex) == 0) {
      SpriteSet spriteSet{};
      
      if (!spriteManager.load(spriteSet, ref.objectType, ref.spriteSetIndex)) {
        return false;
      }
      
      setsRef[ref.spriteSetIndex] = spriteSet;
    }
    
    setsRef[ref.spriteSetIndex].getSprite(sprite, ref.spriteIndex);
    levelMap.sprites.push_back(sprite);
  }
  
  return true;
}

void LevelManager::loadTiles(std::ifstream& levelFile, LevelMap& levelMap) {
  using namespace std;
  
  levelMap.tileSprites.clear();
  levelMap.tiles.clear();
  
  for (unsigned int row = 0; row < levelMap.height; row++) {
    vector<TileInfo> rowTiles{};
    vector<vector<unsigned int>> rowSprites{};
    
    for (unsigned int col = 0; col < levelMap.width; col++) {
      TileInfo info{};
      levelFile.read((char *) &info, sizeof(info));
      
      vector<unsigned int> colSprites{};
      unsigned int layersCount = info.layers;
      unsigned int* layers = new unsigned int[layersCount];
      
      levelFile.read((char *) layers, sizeof(unsigned int) * layersCount);
      
      for (unsigned int layer = 0; layer < layersCount; layer++) {
        colSprites.push_back(layers[layer]);
      }
      
      delete[] layers;
      rowTiles.push_back(info);
      rowSprites.push_back(colSprites);      
    }
    
    levelMap.tiles.push_back(rowTiles);
  }
}
