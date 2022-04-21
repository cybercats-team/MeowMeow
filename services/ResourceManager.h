//
//  ResourceManager.h
//  MeowMeow
//
//  Created by Alex Serdukov on 21.01.2021.
//  Copyright © 2021 Alex Serdukov. All rights reserved.
//

#ifndef ResourceManager_h
#define ResourceManager_h

#include <fstream>
#include <cstring>
#include <utility>

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

#include "../interfaces/Platform.h"
#include "../utils/Debug.h"

extern const char* TEXTURE_BUNDLE_MAGIC;

enum {
  RESOURCE_MAX_PATH = 256,
  RESOURCE_MAX_TITLE = 256
};

enum class ResourceType {
  Image,
  Texture,
  Font,
  Music,
  Sfx,
  TextureBundle
};

enum class BundleType {
  TexturesList,
  TextureInfo,
  LevelsList,
  LevelMap
};

enum class ObjectType {
  Terrain,
  MobileObject
};

using ResourceInfo = struct ResourceInfo {
  std::string resourceTypePath{};
  std::string defaultExtension{};
};

using BundleHeader = struct BundleHeader {
  char magic[7];
  BundleType bundleType = BundleType::TexturesList;
  ObjectType objectType = ObjectType::Terrain;
  unsigned int itemsCount = 0;
  
  BundleHeader() { 
    strcpy(magic, TEXTURE_BUNDLE_MAGIC); 
  }
};

class ResourceManager {
  private:
    static std::map<ResourceType, const ResourceInfo> typesInfo;

    Platform& platform;
    std::string basePath;
  public:
    explicit ResourceManager(Platform& platform);
    std::string getResourcePath(const std::string& resourcePath, ResourceType resourceType);

    bool load(sf::Image& image, const std::string& path);
    bool load(sf::Texture& texture, const std::string& path);
    bool load(std::ifstream& file, const std::string& path, ResourceType resourceType);
    bool load(std::ifstream& file, BundleHeader& header, const std::string& path);
    bool load(sf::Font& font, const std::string& path);
    bool load(sf::Music& music, const std::string& path);
};

#endif /* ResourceManager_h */
