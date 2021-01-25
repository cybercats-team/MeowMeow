//
//  Screen.cpp
//  MeowMeow
//
//  Created by Alex Serdukov on 26.01.2021.
//  Copyright © 2021 Alex Serdukov. All rights reserved.
//

#include "Screen.h"

bool Screen::initialize() {
  using namespace std;
  using namespace sf;
  
  vector<VideoMode> modes = VideoMode::getFullscreenModes();
  
  if (modes.empty()) {
    return false;
  }
  
  selectedMode = move(modes[0]);
  
  float screenWidth = selectedMode.width;
  
  if (screenWidth < 1920) {
    return false;
  }
  
  if (screenWidth >= 2560) {
      scale = screenWidth >= 3840
        ? ScreenScale::UltraHD
        : ScreenScale::RetinaOr2K;
  }
  
  debugPrint(
    "Initialized video mode " +
    to_string(screenWidth) + "x" +
    to_string(selectedMode.height) + ", " +
    to_string(selectedMode.bitsPerPixel) + "-bit colors"
  );
  
  return true;
}

const sf::VideoMode& Screen::getSelectedMode() const {
  return selectedMode;
}

const ScreenScale Screen::getScale() const {
  return scale;
}
