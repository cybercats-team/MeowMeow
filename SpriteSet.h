//
// Created by cyberneticist on 25.01.21.
//

#ifndef MEOWMEOW_SPRITESET_H
#define MEOWMEOW_SPRITESET_H

#include "ResourceManager.h"

typedef struct SpriteSize {
  unsigned int width = 0;
  unsigned int height = 0;
} SpriteSize;

typedef struct SpriteRect: SpriteSize {
  unsigned int left = 0;
  unsigned int top = 0;
} SpriteRect;

typedef struct SpriteFrame {
  SpriteRect rect{};
  SpriteRect rect2x{};
  SpriteRect rect4x{};
} SpriteFrame;

typedef struct SpriteSetInfo {
  char path[RESOURCE_MAX_PATH] = "";
  char path2x[RESOURCE_MAX_PATH] = "";
  char path4x[RESOURCE_MAX_PATH] = "";
  SpriteSize spriteSize{};
  SpriteSize spriteSize2x{};
  SpriteSize spriteSize4x{};
} SpriteSetInfo;

typedef struct SpriteInfo {
  bool animated = false;
  unsigned int animationDuration = 0;
  unsigned int framesCount = 1;
  SpriteFrame frame{};
} SpriteInfo;

class SpriteSet {
  private:
    unsigned int spritesCount = 0;
    const SpriteSetInfo info{};
    std::vector<SpriteInfo> sprites{};
    std::vector<std::vector<SpriteFrame>> frames{};

    friend class SpriteManager;
  public:
    [[nodiscard]] unsigned int getSpritesCount() const;
    [[nodiscard]] const SpriteSetInfo& getInfo() const;
    [[nodiscard]] SpriteInfo& getSprite(unsigned int index) const;
    [[nodiscard]] SpriteFrame& getFrame(unsigned int spriteIndex, unsigned int index) const;
};

#endif //MEOWMEOW_SPRITESET_H
