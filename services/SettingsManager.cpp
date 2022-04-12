#include "SettingsManager.h"

const Settings SettingsManager::defaultSettings = {};

SettingsManager::SettingsManager(Platform& platform) :
  settings(SettingsManager::defaultSettings),
  platform(platform),
  appName("MeowMeow"),
  windowTitle("Meow Meow :: Turkey Hunter") {}

bool SettingsManager::initialize()
{
  //TODO: load from platform
  platform.setAppName(appName);
  return true;
}
  
const Settings& SettingsManager::getSettings()
{
  return settings;
}

