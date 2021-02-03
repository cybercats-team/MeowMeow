//
//  ResourceManager.cpp
//  MeowMeow
//
//  Created by Alex Serdukov on 21.01.2021.
//  Copyright © 2021 Alex Serdukov. All rights reserved.
//

#include "ResourceManager.h"

ResourceManager::ResourceManager(std::string resourcesPath) : basePath(std::move(resourcesPath)) {}

std::string ResourceManager::getResourcePath(const std::string& path, ResourceType resourceType) {
  using namespace std;

  string appendedPath = path;
  const ResourceInfo& info = typesInfo[resourceType];

  if (!hasExtension(appendedPath)) {
    appendedPath += info.defaultExtension;
  }

  if (ds() != '/') {
    replace(appendedPath.begin(), appendedPath.end(), '/', ds());
  }

  return basePath + info.resourceTypePath + ds() + appendedPath;
}

bool ResourceManager::load(sf::Image& image, const std::string& path) {
  return image.loadFromFile(getResourcePath(path, ResourceType::Image));
}

bool ResourceManager::load(sf::Texture& texture, const std::string& path) {
  return texture.loadFromFile(getResourcePath(path, ResourceType::Texture));
}

bool ResourceManager::load(sf::Font& font, const std::string& path) {
  return font.loadFromFile(getResourcePath(path, ResourceType::Font));
}

bool ResourceManager::load(sf::Music& music, const std::string& path) {
  return music.openFromFile(getResourcePath(path, ResourceType::Music));
}

bool ResourceManager::load(std::ifstream& file, BundleHeader& header, const std::string& path) {
  if (!load(file, path, ResourceType::TextureBundle)) {
    debugPrint("Failed to open bundle file");
    return false;
  }
  
  file.read((char *) &header, sizeof(header));
  
  if (strcmp(header.magic, TEXTURE_BUNDLE_MAGIC) != 0) {
    debugPrint("Bundle signature not match");
    file.close();
    return false;
  }
  
  return true;
}

bool ResourceManager::load(std::ifstream& file, const std::string& path, ResourceType resourceType) {
  using namespace std;

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

inline bool ResourceManager::hasExtension(const std::string& resourcePath) {
  using namespace std;

  size_t dotPosition = resourcePath.rfind('.');

  if (dotPosition == string::npos) {
    return false;
  }

  return dotPosition >= (resourcePath.length() - 7);
}
