#include "SettingsManager.h"

const Settings SettingsManager::defaultSettings = {
  .bindings = {
    { ActionType::MoveLeft, {
    }},
    
    { ActionType::MoveRight, {
    }},
    
    { ActionType::MoveUp, {
    }},
    
    { ActionType::MoveDown, {
    }}
  }
};

SettingsManager::SettingsManager(Platform& platform) :
  settings(SettingsManager::defaultSettings),
  platform(platform),
  appName("MeowMeow"),
  windowTitle("Meow Meow :: Turkey Hunter"),
  listeners() {}

bool SettingsManager::initialize()
{  
  platform.setAppName(appName);
  //TODO: load from platform
  emitSettingsUpdated();
  
  return true;
}

void SettingsManager::addListener(SettingsListener& listener)
{
  listeners.push_back(std::ref(listener));
}

void SettingsManager::emitSettingsUpdated() {
  for (auto listener: listeners) {
    SettingsListener& listenerRef = (SettingsListener&) listener;
    
    listenerRef.onSettingsUpdated(settings);
  }
}
  
const Settings& SettingsManager::getSettings()
{
  return settings;
}

const ActionsBindings& SettingsManager::getBindings() {
  return settings.bindings;
}
