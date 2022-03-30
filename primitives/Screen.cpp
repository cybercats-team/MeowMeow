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
  
  selectedMode = modes[0];
  
  unsigned int screenWidth = selectedMode.width;
  
  if (screenWidth < 1920) {
    return false;
  }
  
  if (screenWidth >= 2560) {
      scale = screenWidth >= 3840
        ? ScreenScale::UltraHD
        : ScreenScale::RetinaOr2K;
  }
  
  Debug::printf(
    "Initialized video mode " +
    to_string(screenWidth) + "x" +
    to_string(selectedMode.height) + ", " +
    to_string(selectedMode.bitsPerPixel) + "-bit colors " +
    to_string(static_cast<int>(scale) + 1) + "x scale"
  );
  
  return true;
}

ScreenScale Screen::getScale() const {
  return scale;
}

unsigned int Screen::getWidth() const {
  return selectedMode.width;
}

unsigned int Screen::getHeight() const {
  return selectedMode.height;
}
