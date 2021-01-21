//
//  ResourceManager.h
//  MeowMeow
//
//  Created by Alex Serdukov on 21.01.2021.
//  Copyright © 2021 Alex Serdukov. All rights reserved.
//

#ifndef ResourceManager_h
#define ResourceManager_h

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

class ResourceManager {
  
  private:
    map<string, Image> loadedImages;
    map<string, Texture> loadedTextures;
    map<string, Font> loadedFonts;
    string resourcePath;
    char ds();
  
    string expandPath(string resourcePath, string resourceType);
  
  public:
    ResourceManager(string basePath);
    Image loadImage(string path);
    Texture loadTexture(string path);
    Font loadFont(string path);
    //Music loadMusic(string path);
};

#endif /* ResourceManager_h */
