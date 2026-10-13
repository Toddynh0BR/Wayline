#pragma once
#include <lvgl.h>
namespace wayline::ui::theme {
void initialize();
void applyScreen(lv_obj_t* screen);
void applyTitle(lv_obj_t* label);
void applyMuted(lv_obj_t* label);
void applyAccentButton(lv_obj_t* button);
}
