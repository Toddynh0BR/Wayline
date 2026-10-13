#include "screen_manager.h"
#include "app/app_state.h"
#include "ui/screens/home_screen.h"
#include "ui/screens/navigation_screen.h"
#include "ui/screens/compass_screen.h"
#include "ui/screens/routes_screen.h"
#include "ui/screens/settings_screen.h"
#include "ui/theme.h"
namespace wayline::ui {
namespace {
lv_obj_t* screens[5] = {nullptr, nullptr, nullptr, nullptr, nullptr};
ScreenId active = ScreenId::Home;
lv_obj_t* createScreen(ScreenId id) {
  switch (id) {
    case ScreenId::Home: return createHomeScreen();
    case ScreenId::Navigation: return createNavigationScreen();
    case ScreenId::Compass: return createCompassScreen();
    case ScreenId::Routes: return createRoutesScreen();
    case ScreenId::Settings: return createSettingsScreen();
  }
  return createHomeScreen();
}
}
void begin() {
  // The display adapter must initialize LVGL and register display/touch first.
  theme::initialize();
  for (uint8_t i = 0; i < 5; ++i) screens[i] = createScreen(static_cast<ScreenId>(i));
  showScreen(ScreenId::Home);
}
void showScreen(ScreenId id) {
  const uint8_t index = static_cast<uint8_t>(id);
  if (index >= 5 || screens[index] == nullptr) return;
  active = id;
  app::setCurrentScreen(id);
  lv_scr_load(screens[index]); // LVGL 8 API, like the official Waveshare Arduino example.
}
void update() { if (screens[0] != nullptr) lv_timer_handler(); }
ScreenId visibleScreen() { return active; }
}
