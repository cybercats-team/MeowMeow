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

#include "../interfaces/TypeDefs.h"
#include "../interfaces/Initializable.h"
#include "../utils/Debug.h"

class Screen : public Initializable {
  private:
    sf::VideoMode selectedMode{};
    ScreenScale scale = ScreenScale::FullHD;
  
    friend class Renderer;
    friend class UIManager;
  public:
    bool initialize() override;
    ScreenScale getScale() const;
    unsigned int getWidth() const;
    unsigned int getHeight() const;
};

#endif /* Screen_h */
