#include "SettingsManager.h"

const Settings SettingsManager::defaultSettings = {
  .bindings = {
    { ActionType::MoveLeft, {
      { .type = BindingType::Key, .data = sf::Event::KeyEvent{ .code = sf::Keyboard::A}}
    }},
    
    { ActionType::MoveRight, {
      { .type = BindingType::Key, .data = sf::Event::KeyEvent{ .code = sf::Keyboard::D }}
    }},
    
    { ActionType::MoveUp, {
      { .type = BindingType::Key, .data = sf::Event::KeyEvent{ .code = sf::Keyboard::W }}
    }},
    
    { ActionType::MoveDown, {
      { .type = BindingType::Key, .data = sf::Event::KeyEvent{ .code = sf::Keyboard::S }}
    }},
    
    { ActionType::ButtonA, {
      { .type = BindingType::Key, .data = sf::Event::KeyEvent{ .code = sf::Keyboard::O }},
      { .type = BindingType::MouseButton, .data = sf::Event::MouseButtonEvent{ .button = sf::Mouse::Left }},
      { .type = BindingType::JoystickButton, .data = sf::Event::JoystickButtonEvent{ .button = 0 }}
    }},
    
    { ActionType::ButtonB, {
      { .type = BindingType::Key, .data = sf::Event::KeyEvent{ .code = sf::Keyboard::P }},
      { .type = BindingType::MouseButton, .data = sf::Event::MouseButtonEvent{ .button = sf::Mouse::Right }},
      { .type = BindingType::JoystickButton, .data = sf::Event::JoystickButtonEvent{ .button = 1 }}
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
  listeners.emplace_back(std::ref(listener));
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
