//
//  ResourceManager.cpp
//  MeowMeow
//
//  Created by Alex Serdukov on 21.01.2021.
//  Copyright © 2021 Alex Serdukov. All rights reserved.
//

#include "ResourceManager.h"

std::map<ResourceType, const ResourceInfo> ResourceManager::typesInfo {
  { ResourceType::Image, { .resourceTypePath = "images", .defaultExtension = ".png" } },
  { ResourceType::Texture, { .resourceTypePath = "textures", .defaultExtension = ".png" } },
  { ResourceType::Font, { .resourceTypePath = "fonts", .defaultExtension = ".ttf" } },
  { ResourceType::Music, { .resourceTypePath = "music", .defaultExtension = ".ogg" } },
  { ResourceType::Sfx, { .resourceTypePath = "sounds", .defaultExtension = ".wav" } },
  { ResourceType::TextureBundle, { .resourceTypePath = "bundles", .defaultExtension = ".bundle" } }
};

ResourceManager::ResourceManager(Platform& platform)
  : platform(platform), basePath(platform.resourcePath()) {}

std::string ResourceManager::getResourcePath(const std::string& resourcePath, ResourceType resourceType) {
  using namespace std;
  using namespace std::filesystem;

  const ResourceInfo& info = typesInfo[resourceType];
  path normalizedPath = path(resourcePath).lexically_normal();

  if (!normalizedPath.has_extension()) {
    normalizedPath += info.defaultExtension;
  }

  path fullPath(basePath);

  fullPath /= info.resourceTypePath;
  fullPath /= normalizedPath;

  return fullPath.string();
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
    Debug::printf("Failed to open bundle file");
    return false;
  }

  file.read((char *) &header, sizeof(header));

  if (strcmp(header.magic, TEXTURE_BUNDLE_MAGIC) != 0) {
    Debug::printf("Bundle signature not match");
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
