#pragma once
#include <stdint.h>
namespace wayline {
enum class ScreenId : uint8_t { Home, Navigation, Compass, Routes, Settings };
enum class NavigationMode : uint8_t { Compass, NextTurn, Route, Map };
enum class TurnDirection : uint8_t { None, Straight, Left, Right, UTurn };
struct NavigationState {
  bool gpsFix = false;
  double latitude = 0.0;
  double longitude = 0.0;
  float speedKmh = 0.0F;
  uint8_t satellites = 0;
  uint32_t distanceToTurnM = 0;
  TurnDirection nextTurn = TurnDirection::None;
  bool routeLoaded = false;
  uint32_t distanceToDestinationM = 0;
};
}
