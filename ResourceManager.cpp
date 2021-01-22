//
//  ResourceManager.cpp
//  MeowMeow
//
//  Created by Alex Serdukov on 21.01.2021.
//  Copyright © 2021 Alex Serdukov. All rights reserved.
//

#include "ResourceManager.h"

ResourceManager::ResourceManager(string resourcesPath) : basePath(move(resourcesPath)) {}

bool ResourceManager::load(Image& image, const string& path) {
  return image.loadFromFile(expandPath(path, ResourceType::Image));
}

bool ResourceManager::load(Texture& texture, const string& path) {
  return texture.loadFromFile(expandPath(path, ResourceType::Texture));
}

bool ResourceManager::load(Font& font, const string& path) {
  return font.loadFromFile(expandPath(path, ResourceType::Font));
}

bool ResourceManager::load(Music& music, const string& path) {
  return music.openFromFile(expandPath(path, ResourceType::Music));
}

inline char ResourceManager::ds() {
#ifdef _WIN32
  return '\\';
#else
  return '/';
#endif
}

inline bool ResourceManager::hasExtension(const string& resourcePath) {
  size_t dotPosition = resourcePath.find_last_of('.');

  if (dotPosition == string::npos) {
    return false;
  }

  return dotPosition >= (resourcePath.length() - 5);
}

string ResourceManager::expandPath(const string& path, ResourceType resourceType) {
  string appendedPath = path;
  ResourceInfo& info = resourceTypesInfo[resourceType];

  if (!hasExtension(appendedPath)) {
    appendedPath += info.defaultExtension;
  }

  if (ds() != '/') {
    replace(appendedPath.begin(), appendedPath.end(), '/', ds());
  }

  return basePath + info.resourceTypePath + ds() + appendedPath;
}
