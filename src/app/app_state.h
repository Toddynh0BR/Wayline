#pragma once
#include "wayline_types.h"
namespace wayline::app {
NavigationState& navigationState();
ScreenId currentScreen();
void setCurrentScreen(ScreenId id);
NavigationMode navigationMode();
void setNavigationMode(NavigationMode mode);
}
