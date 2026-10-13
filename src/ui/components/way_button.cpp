#include "way_button.h"
#include "ui/theme.h"
namespace wayline::ui::components {
lv_obj_t* createWayButton(lv_obj_t* parent, const char* text, lv_event_cb_t callback, void* userData) {
  lv_obj_t* button = lv_btn_create(parent);
  lv_obj_set_size(button, 210, 48);
  theme::applyAccentButton(button);
  lv_obj_add_event_cb(button, callback, LV_EVENT_CLICKED, userData);
  lv_obj_t* label = lv_label_create(button);
  lv_label_set_text(label, text);
  lv_obj_center(label);
  lv_obj_set_style_text_color(label, lv_color_hex(0xFFFFFF), 0);
  lv_obj_set_style_text_font(label, &lv_font_montserrat_16, 0);
  return button;
}
}
