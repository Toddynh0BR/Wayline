#include "app_state.h"
namespace wayline::app {
namespace { NavigationState state{}; ScreenId activeScreen = ScreenId::Home; NavigationMode activeMode = NavigationMode::Compass; }
NavigationState& navigationState() { return state; }
ScreenId currentScreen() { return activeScreen; }
void setCurrentScreen(ScreenId id) { activeScreen = id; }
NavigationMode navigationMode() { return activeMode; }
void setNavigationMode(NavigationMode mode) { activeMode = mode; }
}
