//
//  Screen.hpp
//  MeowMeow
//
//  Created by Alex Serdukov on 26.01.2021.
//  Copyright © 2021 Alex Serdukov. All rights reserved.
//

#ifndef Screen_h
#define Screen_h

#include <SFML/Graphics.hpp>

#include "Debug.h"

enum class ScreenScale {
  FullHD,
  RetinaOr2K,
  UltraHD
};

class Screen {
  private:
    sf::VideoMode selectedMode{};
    ScreenScale scale = ScreenScale::FullHD;
  
    friend class Application;
    friend class SpriteManager;
  public:
    bool initialize();
    [[nodiscard]] ScreenScale getScale() const;
    [[nodiscard]] unsigned int getWidth() const;
    [[nodiscard]] unsigned int getHeight() const;
};

#endif /* Screen_h */
