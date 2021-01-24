//
//  ResourceManager.cpp
//  MeowMeow
//
//  Created by Alex Serdukov on 21.01.2021.
//  Copyright © 2021 Alex Serdukov. All rights reserved.
//

#include "ResourceManager.h"

map<ResourceType, const ResourceInfo> ResourceManager::resourceTypesInfo = {
  {ResourceType::Image, { .resourceTypePath = "images", .defaultExtension = ".png" }},
  {ResourceType::Texture, { .resourceTypePath = "textures", .defaultExtension = ".png" }},
  {ResourceType::Font, { .resourceTypePath = "fonts", .defaultExtension = ".ttf" }},
  {ResourceType::Music, { .resourceTypePath = "music", .defaultExtension = ".ogg" }},
  {ResourceType::Sfx, { .resourceTypePath = "sounds", .defaultExtension = ".wav" }},
  {ResourceType::TextureBundle, { .resourceTypePath = "bundles", .defaultExtension = ".bundle" }}
};

ResourceManager::ResourceManager(string resourcesPath) : basePath(move(resourcesPath)) {}

string ResourceManager::getResourcePath(const string& path, ResourceType resourceType) {
  string appendedPath = path;
  const ResourceInfo& info = resourceTypesInfo[resourceType];

  if (!hasExtension(appendedPath)) {
    appendedPath += info.defaultExtension;
  }

  if (ds() != '/') {
    replace(appendedPath.begin(), appendedPath.end(), '/', ds());
  }

  return basePath + info.resourceTypePath + ds() + appendedPath;
}

bool ResourceManager::load(Image& image, const string& path) {
  return image.loadFromFile(getResourcePath(path, ResourceType::Image));
}

bool ResourceManager::load(Texture& texture, const string& path) {
  return texture.loadFromFile(getResourcePath(path, ResourceType::Texture));
}

bool ResourceManager::load(Font& font, const string& path) {
  return font.loadFromFile(getResourcePath(path, ResourceType::Font));
}

bool ResourceManager::load(Music& music, const string& path) {
  return music.openFromFile(getResourcePath(path, ResourceType::Music));
}

bool ResourceManager::load(ifstream& file, const string& path, ResourceType resourceType) {
  file.open(getResourcePath(path, resourceType), ifstream::in | ifstream::binary);
  
  if (!file) {
    return false;
  }
  
  return true;
}

inline char ResourceManager::ds() {
#ifdef _WIN32
  return '\\';
#else
  return '/';
#endif
}

inline bool ResourceManager::hasExtension(const string& resourcePath) {
  size_t dotPosition = resourcePath.rfind('.');

  if (dotPosition == string::npos) {
    return false;
  }

  return dotPosition >= (resourcePath.length() - 7);
}
