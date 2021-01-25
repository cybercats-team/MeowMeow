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
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

#define RESOURCE_MAX_PATH 256

enum class ResourceType {
  Image,
  Texture,
  Font,
  Music,
  Sfx,
  TextureBundle
};

typedef struct {
  std::string resourceTypePath;
  std::string defaultExtension;
} ResourceInfo;

class ResourceManager {
  
  private:
    std::map<ResourceType, const ResourceInfo> typesInfo = {
      {ResourceType::Image, { .resourceTypePath = "images", .defaultExtension = ".png" }},
      {ResourceType::Texture, { .resourceTypePath = "textures", .defaultExtension = ".png" }},
      {ResourceType::Font, { .resourceTypePath = "fonts", .defaultExtension = ".ttf" }},
      {ResourceType::Music, { .resourceTypePath = "music", .defaultExtension = ".ogg" }},
      {ResourceType::Sfx, { .resourceTypePath = "sounds", .defaultExtension = ".wav" }},
      {ResourceType::TextureBundle, { .resourceTypePath = "bundles", .defaultExtension = ".bundle" }}
    };

    std::string basePath;

    // private FS helpers
    static char ds();
    static bool hasExtension(const std::string& resourcePath);
    
  
  public:
    explicit ResourceManager(std::string  basePath);
    std::string getResourcePath(const std::string& resourcePath, ResourceType resourceType);
  
    bool load(sf::Image& image, const std::string& path);
    bool load(sf::Texture& texture, const std::string& path);
    bool load(sf::Font& font, const std::string& path);
    bool load(sf::Music& music, const std::string& path);
    bool load(std::ifstream& file, const std::string& path, ResourceType resourceType);
};

#endif /* ResourceManager_h */
