//
//  LevelManager.cpp
//  MeowMeow
//
//  Created by Alex Serdukov on 16.02.2021.
//  Copyright © 2021 Alex Serdukov. All rights reserved.
//

#include "LevelManager.h"

LevelManager::LevelManager(SpriteManager& spriteManager, ResourceManager& resourceManager, Screen& screen):
  UIManager(resourceManager, screen),
  spriteManager(spriteManager),
  realms({}),
  levels({}) {}

bool LevelManager::initialize() {
  using namespace std;

  ifstream listFile;
  BundleHeader header{};
  RealmInfo info{};

  Debug::printf("Loading bundle %s", bundlePath);

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

      Debug::printf("Added level %s", levelInfo.path);
    }

    levels.push_back(levelsList);
    realms.push_back(info);
  }

  return true;
}

unsigned long LevelManager::getRealmsCount() {
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
    Debug::printf("Realm #%d not exists", realmId);
    return false;
  }

  vector<LevelInfo>& realmLevels = levels[realmId];

  if (levelId > realmLevels.size()) {
    Debug::printf("Level #%d.%d not exists", realmId, levelId);
    return false;
  }

  ifstream levelFile;
  BundleHeader header {};
  string path(realmLevels[levelId].path);

  Debug::printf("Loading bundle %s", path);

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
  return screenQuery(info.tileSize, info.tileSize2k, info.tileSize4k);
}

bool LevelManager::loadSprites(std::ifstream& levelFile, LevelMap& levelMap, unsigned int spritesCount) {
  using namespace std;

  map<ObjectType, vector<unsigned int>> mapSpriteSets = {
    {ObjectType::Terrain, {}},
    {ObjectType::MobileObject, {}}
  };

  levelMap.sprites.clear();

  for (unsigned int spriteIndex = 0; spriteIndex < spritesCount; spriteIndex++) {
    SpriteRef ref{};
    levelFile.read((char *) &ref, sizeof(ref));

    map<unsigned int, SpriteSet>& setsRef = spriteSets[ref.objectType];
    vector<unsigned int>& mapSetsRef = mapSpriteSets[ref.objectType];

    if (!Array::includes(mapSetsRef, ref.spriteSetIndex)) {
      mapSetsRef.push_back(ref.spriteSetIndex);
    }

    if (setsRef.count(ref.spriteSetIndex) == 0) {
      SpriteSet spriteSet{};

      if (!spriteManager.load(spriteSet, ref.objectType, ref.spriteSetIndex)) {
        return false;
      }

      setsRef[ref.spriteSetIndex] = spriteSet;
    }

    SpriteObject sprite{};
    SpriteSet& spriteSetRef = setsRef[ref.spriteSetIndex];

    spriteSetRef.getSprite(sprite, ref.spriteIndex);
    levelMap.sprites.push_back(sprite);
  }

  disposeSpritesUnused(mapSpriteSets);
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
      auto* layers = new unsigned int[layersCount];

      levelFile.read((char *) layers, sizeof(unsigned int) * layersCount);

      for (unsigned int layer = 0; layer < layersCount; layer++) {
        colSprites.push_back(layers[layer]);
      }

      delete[] layers;
      rowTiles.push_back(info);
      rowSprites.push_back(colSprites);
    }

    levelMap.tileSprites.push_back(rowSprites);
    levelMap.tiles.push_back(rowTiles);
  }
}

void LevelManager::disposeSpritesUnused(std::map<ObjectType, std::vector<unsigned int>>& spriteSetsUsed) {
  using namespace std;

  map<ObjectType, vector<unsigned int>> unusedSpriteSets = {
    {ObjectType::Terrain, {}},
    {ObjectType::MobileObject, {}}
  };

  for (const auto& typesSets: spriteSets) {
    ObjectType objectType = typesSets.first;
    vector<unsigned int>& mapSetsRef = spriteSetsUsed[objectType];

    for (const auto& sets: spriteSets[objectType]) {
      unsigned int spriteSetId = sets.first;

      if (!Array::includes(mapSetsRef, spriteSetId)) {
        unusedSpriteSets[objectType].push_back(spriteSetId);
      }
    }
  }

  for (const auto& typesSets: unusedSpriteSets) {
    ObjectType objectType = typesSets.first;
    map<unsigned int, SpriteSet>& setsRef = spriteSets[objectType];

    for (const auto& spriteSetId: unusedSpriteSets[objectType]) {
      setsRef.erase(spriteSetId);
    }
  }
}
