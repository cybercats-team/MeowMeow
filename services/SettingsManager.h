#ifndef SETTINGS_MANAGER_H
#define SETTINGS_MANAGER_H

#include <SFML/Window.hpp>
#include <map>
#include <string>
#include <functional>
#include <vector>
#include <variant>

#include "../interfaces/Platform.h"
#include "../interfaces/Initializable.h"
#include "../interfaces/EventHandler.h"

#include "../utils/Debug.h"

enum class BindingType {
  Key,
  MouseButton,
  JoystickButton,
  JoystickAxis,
  JoystickMove,
  MouseMove
};

using KeyBinding = sf::Event::KeyEvent;
using MouseBinding = sf::Event::MouseButtonEvent;
using JoystickBinding = sf::Event::JoystickButtonEvent;
using JoystickAxisBinding = sf::Event::JoystickMoveEvent;

using JoystickMoveBinding = struct JoystickMoveBinding {
  unsigned int joystickId;
  sf::Joystick::Axis axisX;
  sf::Joystick::Axis axisY;
};

using BindingData = std::variant<
  KeyBinding,
  MouseBinding,
  JoystickBinding,
  JoystickMoveBinding,
  JoystickAxisBinding
>;

using ActionBinding = struct ActionBinding {
  BindingType type;
  BindingData data{};
};

using ActionsBindings = std::map<
  ActionType,
  std::vector<ActionBinding>
>;

using Settings = struct Settings {
  ActionsBindings bindings{};
};

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
