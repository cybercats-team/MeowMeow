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

const std::map<sf::Event::EventType, BindingType> SettingsManager::bindingTypesByEvent = {
  { sf::Event::EventType::KeyPressed, BindingType::Key },
  { sf::Event::EventType::KeyReleased, BindingType::Key },
  { sf::Event::EventType::MouseButtonPressed, BindingType::MouseButton },
  { sf::Event::EventType::MouseButtonReleased, BindingType::MouseButton },
  { sf::Event::EventType::JoystickButtonPressed, BindingType::JoystickButton },
  { sf::Event::EventType::JoystickButtonReleased, BindingType::JoystickButton },
  { sf::Event::EventType::MouseMoved, BindingType::MouseMove },
  { sf::Event::EventType::JoystickMoved, BindingType::JoystickMove }
};

BindingType SettingsManager::getBingingType(sf::Event event) {
  return getBingingType(event.type);
}

BindingType SettingsManager::getBingingType(sf::Event::EventType eventType) {
  auto keyValuePair = bindingTypesByEvent.find(eventType);
  
  if (keyValuePair == bindingTypesByEvent.end()) {
    return BindingType::None;
  }
  
  return keyValuePair->second;
}

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
