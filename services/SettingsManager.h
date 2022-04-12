#ifndef SETTINGS_MANAGER_H
#define SETTINGS_MANAGER_H

#include <string>

#include "../interfaces/TypeDefs.h"
#include "../interfaces/Platform.h"
#include "../interfaces/Initializable.h"

class SettingsManager : public Initializable
{ 
  private:
    Settings settings;       
  
  public:
    const std::string appName;
    const std::string windowTitle;
    Platform& platform;
  
    explicit SettingsManager(Platform& platform);
    bool initialize() override;
    
    const Settings& getSettings();
  
    static const Settings defaultSettings;  
};

#endif // SETTINGS_MANAGER_H
