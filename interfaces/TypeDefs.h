//
//  TypeDefs.h
//  MeowMeow
//
//  Created by Alex Serdukov on 1/23/21.
//  Copyright © 2021 Alex Serdukov. All rights reserved.
//

#ifndef TypeDefs_h
#define TypeDefs_h

#include <SFML/Window.hpp>
#include <string>
#include <variant>
#include <vector>
#include <map>

#define RESOURCE_MAX_PATH 256
#define RESOURCE_MAX_TITLE 256
#define TEXTURE_BUNDLE_MAGIC "BUNDLE"

enum class ScreenScale {
  FullHD,
  RetinaOr2K,
  UltraHD
};

enum class ResourceType {
  Image,
  Texture,
  Font,
  Music,
  Sfx,
  TextureBundle
};

enum class BundleType {
  TexturesList,
  TextureInfo [[maybe_unused]],
  LevelsList [[maybe_unused]],
  LevelMap
};

enum class ObjectType {
  Terrain,
  MobileObject
};

enum class TileType {
  Terrain,
  Obstacle [[maybe_unused]]
};

enum class ActionType {
  MoveLeft,
  MoveRight,
  MoveUp,
  MoveDown,
  ButtonA,
  ButtonB,
  ButtonC,
  ButtonD,
  LeftStick,
  LeftShift,
  LeftTrigger,
  LeftClick,
  RightStick,
  RightShift,
  RightTrigger,
  RightClick,
  Home,
  Share,
  Options,
  AltOptions
};

enum class ActionEventType {
  ActionPressed,
  ActionReleased,
  ActionStickMoved
};

enum class BindingType {
  Key,
  MouseButton,
  MouseMove,
  JoystickButton,
  JoystickMove
};    

using ResourceInfo = struct ResourceInfo {
  std::string resourceTypePath{};
  std::string defaultExtension{};
};

using BundleHeader = struct BundleHeader {
  char magic[7] = TEXTURE_BUNDLE_MAGIC;
  BundleType bundleType = BundleType::TexturesList;
  ObjectType objectType = ObjectType::Terrain;
  unsigned int itemsCount = 0;
};

using Dimensions = struct Dimensions {
  unsigned int width = 0;
  unsigned int height = 0;
};

using SpriteInfo = struct SpriteInfo {
  bool animated = false;
  unsigned int animationDuration = 0;
  unsigned int framesCount = 1;
};

using Rectangle = struct Rectangle
  : public Dimensions 
{
  unsigned int left = 0;
  unsigned int top = 0;
};

using SpriteFrame = struct SpriteFrame {
  Rectangle rect{};
  Rectangle rect2k{};
  Rectangle rect4k{};
};

using RealmInfo = struct RealmInfo {
  char realmName[RESOURCE_MAX_TITLE] = "";
  unsigned int levelsCount = 0;
};

using LevelInfo = struct LevelInfo {
  char levelName[RESOURCE_MAX_TITLE] = "";
  char path[RESOURCE_MAX_PATH] = "";
};

using SpriteRef = struct SpriteRef {
  ObjectType objectType = ObjectType::Terrain;
  unsigned int spriteSetIndex = 0;
  unsigned int spriteIndex = 0;
};

using TileInfo = struct TileInfo {
  unsigned int layers = 1;
  TileType type = TileType::Terrain;
};

using AggregatedMapInfo = struct AggregatedMapInfo
  : public Dimensions 
{
  unsigned int borderTile = 0;
  Dimensions tileSize{};
};

using TextureItem = struct TextureInfo {
  char infoPath[RESOURCE_MAX_PATH] = "";
};

using SpriteSetInfo = struct SpriteSetInfo {
  char path[RESOURCE_MAX_PATH] = "";
  char path2k[RESOURCE_MAX_PATH] = "";
  char path4k[RESOURCE_MAX_PATH] = "";
  Dimensions spriteSize{};
  Dimensions spriteSize2k{};
  Dimensions spriteSize4k{};
};

using MapInfo = struct MapInfo
  : public AggregatedMapInfo 
{
  unsigned int spriteRefsCount = 0;
  Dimensions tileSize2k{};
  Dimensions tileSize4k{};
};

using StickMoveDetails = struct StickMoveDetails {
  float positionX;
  float positionY;
};

using BindingData = std::variant<
  sf::Event::KeyEvent,
  sf::Event::MouseButtonEvent,
  sf::Event::MouseMoveEvent,
  sf::Event::JoystickMoveEvent,
  sf::Event::JoystickButtonEvent
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

using ActionMapping = struct ActionMapping {
  ActionType action;
  BindingData data{};
};

using EventActionMapping = struct EventActionMapping {
  sf::Event::EventType event; 
  ActionEventType action;
};

using AggregatedActionMapping = struct AggregatedActionMapping {
  BindingType bindingType;
  ActionEventType actionType;
  std::vector<ActionMapping> bindings{};
};

#endif /* TypeDefs_h */