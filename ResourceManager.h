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

using namespace sf;
using namespace std;

enum class ResourceType {
  Image,
  Texture,
  Font,
  Music,
  Sfx,
  TextureBundle
};

typedef struct {
  string resourceTypePath;
  string defaultExtension;
} ResourceInfo;

class ResourceManager {
  
  private:
    static map<ResourceType, const ResourceInfo> resourceTypesInfo;
  
    string basePath;

    // private FS helpers
    static char ds();
    static bool hasExtension(const string& resourcePath);
    
  
  public:
    explicit ResourceManager(string  basePath);
    string getResourcePath(const string& resourcePath, ResourceType resourceType);
  
    bool load(Image& image, const string& path);
    bool load(Texture& texture, const string& path);
    bool load(Font& font, const string& path);
    bool load(Music& music, const string& path);
    bool load(ifstream& file, const string& path, ResourceType resourceType);
};

#endif /* ResourceManager_h */
