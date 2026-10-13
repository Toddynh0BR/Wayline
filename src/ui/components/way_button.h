#pragma once
#include <lvgl.h>
namespace wayline::ui::components {
lv_obj_t* createWayButton(lv_obj_t* parent, const char* text, lv_event_cb_t callback, void* userData = nullptr);
}
