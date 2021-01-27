//
// Created by cyberneticist on 25.01.21.
//

#ifndef MEOWMEOW_SPRITESET_H
#define MEOWMEOW_SPRITESET_H

#include "Screen.h"
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
  SpriteRect rect2k{};
  SpriteRect rect4k{};
} SpriteFrame;

typedef struct SpriteSetInfo {
  char path[RESOURCE_MAX_PATH] = "";
  char path2k[RESOURCE_MAX_PATH] = "";
  char path4k[RESOURCE_MAX_PATH] = "";
  SpriteSize spriteSize{};
  SpriteSize spriteSize2k{};
  SpriteSize spriteSize4k{};
} SpriteSetInfo;

typedef struct SpriteInfo {
  bool animated = false;
  unsigned int animationDuration = 0;
  unsigned int framesCount = 1;
} SpriteInfo;

class SpriteSet {
  private:
    ScreenScale scale = ScreenScale::FullHD;
    unsigned int spritesCount = 0;
    const SpriteSetInfo info{};
    std::vector<SpriteInfo> sprites{};
    std::vector<std::vector<SpriteFrame>> frames{};

    friend class SpriteManager;
  public:
    [[nodiscard]] unsigned int getSpritesCount() const;
    [[nodiscard]] const SpriteSetInfo& getInfo() const;
    [[nodiscard]] std::string getTexturePath() const;
    [[nodiscard]] const SpriteSize& getSpriteSize() const;
    [[nodiscard]] const SpriteInfo& getSpriteInfo(unsigned int index) const;
    [[nodiscard]] const SpriteRect& getFrameRect(unsigned int spriteIndex, unsigned int index = 0) const;
};

#endif //MEOWMEOW_SPRITESET_H
