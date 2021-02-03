//
//  TypeDefs.h
//  MeowMeow
//
//  Created by Alex Serdukov on 1/23/21.
//  Copyright © 2021 Alex Serdukov. All rights reserved.
//

#ifndef TypeDefs_h
#define TypeDefs_h

#define RESOURCE_MAX_PATH 256
#define TEXTURE_BUNDLE_MAGIC "BUNDLE"

enum class ScreenScale {
  FullHD,
  RetinaOr2K,
  UltraHD
};

enum class ResourceType {
  Image,
  Texture,
  Font,
  Music,
  Sfx,
  TextureBundle
};

enum class BundleType {
  TexturesList,
  TextureInfo,
  LevelMap
};

enum class ObjectType {
  Terrain,
  MobileObject
};

typedef struct ResourceInfo {
  std::string resourceTypePath;
  std::string defaultExtension;
} ResourceInfo;

typedef struct BundleHeader {
  char magic[7] = TEXTURE_BUNDLE_MAGIC;
  BundleType bundleType = BundleType::TexturesList;
  ObjectType objectType = ObjectType::Terrain;
  unsigned int itemsCount = 0;
} BundleHeader;

typedef struct Dimensions {
  unsigned int width = 0;
  unsigned int height = 0;
} Dimensions;

typedef struct SpriteInfo {
  bool animated = false;
  unsigned int animationDuration = 0;
  unsigned int framesCount = 1;
} SpriteInfo;

typedef struct Rectangle: Dimensions {
  unsigned int left = 0;
  unsigned int top = 0;
} Rectangle;

typedef struct SpriteFrame {
  Rectangle rect{};
  Rectangle rect2k{};
  Rectangle rect4k{};
} SpriteFrame;

typedef struct SpriteRef {
  ObjectType objectType = ObjectType::Terrain;
  unsigned int spriteSetIndex = 0;
  unsigned int spriteIndex = 0;
} SpriteRef;

typedef struct TileInfo {
  unsigned int layers = 1;
} TileInfo;

typedef struct AggredatedMapInfo {
  unsigned int width = 0;
  unsigned int height = 0;
  Dimensions tileSize{};
} AggredatedMapInfo;

typedef struct TextureInfo {
  char infoPath[RESOURCE_MAX_PATH] = "";
} TextureItem;

typedef struct SpriteSetInfo {
  char path[RESOURCE_MAX_PATH] = "";
  char path2k[RESOURCE_MAX_PATH] = "";
  char path4k[RESOURCE_MAX_PATH] = "";
  Dimensions spriteSize{};
  Dimensions spriteSize2k{};
  Dimensions spriteSize4k{};
} SpriteSetInfo;

typedef struct MapInfo: AggredatedMapInfo {
  Dimensions tileSize2k{};
  Dimensions tileSize4k{};
  SpriteRef borderTile{};
} MapInfo;

#endif /* TypeDefs_h */
