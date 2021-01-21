//
//  ResourceManager.cpp
//  MeowMeow
//
//  Created by Alex Serdukov on 21.01.2021.
//  Copyright © 2021 Alex Serdukov. All rights reserved.
//

#include "ResourceManager.h"

ResourceManager::ResourceManager(string basePath) :
  resourcePath(basePath),
  loadedImages(),
  loadedTextures(),
  loadedFonts() {}

Image ResourceManager::loadImage(string path) {
  if (loadedImages.find(path) != loadedImages.end()) {
    return loadedImages[path];
  }
  
  Image image;
    
  if (!image.loadFromFile(expandPath(path, "images"))) {
    throw runtime_error("Unable to load image " + path);
  }
    
  loadedImages[path] = image;
  return image;
}

Texture ResourceManager::loadTexture(string path) {
  if (loadedTextures.find(path) != loadedTextures.end()) {
    return loadedTextures[path];
  }
  
  Texture texture;
    
  if (!texture.loadFromFile(expandPath(path, "textures"))) {
    throw runtime_error("Unable to load texture " + path);
  }
    
  loadedTextures[path] = texture;
  return texture;
}

Font ResourceManager::loadFont(string path) {
  if (loadedFonts.find(path) != loadedFonts.end()) {
    return loadedFonts[path];
  }
  
  Font font;
    
  if (!font.loadFromFile(expandPath(path, "fonts"))) {
    throw runtime_error("Unable to load font " + path);
  }
    
  loadedFonts[path] = font;
  return font;
}

/*Music ResourceManager::loadMusic(string path) {
  Music music;
    
  if (!music.openFromFile(expandPath(path, "music"))) {
    throw runtime_error("Unable to load image " + path);
  }
    
  return music;
}*/

inline char ResourceManager::ds() {
#ifdef _WIN32
  return '\\';
#else
  return '/';
#endif
}

string ResourceManager::expandPath(string path, string resourceType) {
  string expandedPath = resourcePath + resourceType + ds() + path;
  
  replace(expandedPath.begin(), expandedPath.end(), '/', ds());
  return expandedPath;
}
