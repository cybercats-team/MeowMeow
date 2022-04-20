#ifndef SETTINGS_MANAGER_H
#define SETTINGS_MANAGER_H

#include <SFML/Window.hpp>
#include <map>
#include <string>
#include <functional>
#include <vector>

#include "../interfaces/TypeDefs.h"
#include "../interfaces/Platform.h"
#include "../interfaces/Initializable.h"

#include "../utils/Debug.h"

class SettingsListener {
  public:
    virtual void onSettingsUpdated(const Settings& settings) = 0;
};

class SettingsManager : public Initializable
{ 
  private:    
    Settings settings;
    std::vector<std::reference_wrapper<SettingsListener>> listeners;
    
    void emitSettingsUpdated();
  
    static const Settings defaultSettings;    
  public:
    const std::string appName;
    const std::string windowTitle;
    Platform& platform;
  
    explicit SettingsManager(Platform& platform);
    bool initialize() override;
    void addListener(SettingsListener& listener);
    
    const Settings& getSettings();
    const ActionsBindings& getBindings();
};

#endif // SETTINGS_MANAGER_H
