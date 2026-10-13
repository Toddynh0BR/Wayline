#include "status_pill.h"
namespace wayline::ui::components {
lv_obj_t* createStatusPill(lv_obj_t* parent, const char* text, bool online) {
  lv_obj_t* pill = lv_obj_create(parent);
  lv_obj_set_size(pill, LV_SIZE_CONTENT, 28);
  lv_obj_set_style_radius(pill, LV_RADIUS_CIRCLE, 0);
  lv_obj_set_style_pad_hor(pill, 12, 0);
  lv_obj_set_style_pad_ver(pill, 4, 0);
  lv_obj_set_style_border_width(pill, 0, 0);
  lv_obj_set_style_bg_color(pill, lv_color_hex(online ? 0x123D2A : 0x303039), 0);
  lv_obj_set_style_bg_opa(pill, LV_OPA_COVER, 0);
  lv_obj_t* label = lv_label_create(pill);
  lv_label_set_text(label, text);
  lv_obj_set_style_text_color(label, lv_color_hex(online ? 0x78E0A1 : 0xB7B7C2), 0);
  lv_obj_center(label);
  return pill;
}
}
