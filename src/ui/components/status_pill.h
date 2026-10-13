#pragma once
#include <lvgl.h>
namespace wayline::ui::components {
lv_obj_t* createStatusPill(lv_obj_t* parent, const char* text, bool online);
}
