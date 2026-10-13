#pragma once
#include <lvgl.h>
#include "wayline_types.h"
namespace wayline::ui {
void begin();
void update();
void showScreen(ScreenId id);
ScreenId visibleScreen();
}
