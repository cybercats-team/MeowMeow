#include "SettingsManager.h"

const Settings SettingsManager::defaultSettings = {
  .bindings = {
    { ActionType::MoveLeft, {
      { .type = BindingType::Key, .data = KeyBinding{ .code = sf::Keyboard::A }},
      { .type = BindingType::JoystickAxis, .data = JoystickAxisBinding{ .axis = sf::Joystick::PovX, .position = -1 }}
    }},
    
    { ActionType::MoveRight, {
      { .type = BindingType::Key, .data = KeyBinding{ .code = sf::Keyboard::D }},
      { .type = BindingType::JoystickAxis, .data = JoystickAxisBinding{ .axis = sf::Joystick::PovX, .position = 1 }}
    }},
    
    { ActionType::MoveUp, {
      { .type = BindingType::Key, .data = KeyBinding{ .code = sf::Keyboard::W }},
      { .type = BindingType::JoystickAxis, .data = JoystickAxisBinding{ .axis = sf::Joystick::PovY, .position = -1 }}
    }},
    
    { ActionType::MoveDown, {
      { .type = BindingType::Key, .data = KeyBinding{ .code = sf::Keyboard::S }},
      { .type = BindingType::JoystickAxis, .data = JoystickAxisBinding{ .axis = sf::Joystick::PovY, .position = 1 }}
    }},
    
    { ActionType::ButtonA, {
      { .type = BindingType::Key, .data = KeyBinding{ .code = sf::Keyboard::O }},
      { .type = BindingType::MouseButton, .data = MouseBinding{ .button = sf::Mouse::Left }},
      { .type = BindingType::JoystickButton, .data = JoystickBinding{ .button = 0 }}
    }},
    
    { ActionType::ButtonB, {
      { .type = BindingType::Key, .data = KeyBinding{ .code = sf::Keyboard::P }},
      { .type = BindingType::MouseButton, .data = MouseBinding{ .button = sf::Mouse::Right }},
      { .type = BindingType::JoystickButton, .data = JoystickBinding{ .button = 1 }}
    }},
    
    { ActionType::LeftStick, {
      { .type = BindingType::JoystickMove, .data = JoystickMoveBinding{ .axisX = sf::Joystick::X, .axisY = sf::Joystick::Y }}
    }},
    
    { ActionType::RightStick, {
      { .type = BindingType::JoystickMove, .data = JoystickMoveBinding{ .axisX = sf::Joystick::U, .axisY = sf::Joystick::V }},
      { .type = BindingType::MouseMove }
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
