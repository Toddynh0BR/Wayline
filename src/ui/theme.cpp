#include "theme.h"
namespace wayline::ui::theme {
void initialize() {}
void applyScreen(lv_obj_t* screen) {
  lv_obj_set_style_bg_color(screen, lv_color_hex(0x08090C), 0);
  lv_obj_set_style_bg_opa(screen, LV_OPA_COVER, 0);
  lv_obj_set_style_border_width(screen, 0, 0);
  lv_obj_set_style_pad_all(screen, 20, 0);
}
void applyTitle(lv_obj_t* label) {
  lv_obj_set_style_text_color(label, lv_color_hex(0xFFFFFF), 0);
  lv_obj_set_style_text_font(label, &lv_font_montserrat_28, 0);
}
void applyMuted(lv_obj_t* label) { lv_obj_set_style_text_color(label, lv_color_hex(0x9CA3AF), 0); }
void applyAccentButton(lv_obj_t* button) {
  lv_obj_set_style_bg_color(button, lv_color_hex(0xE53935), 0);
  lv_obj_set_style_bg_opa(button, LV_OPA_COVER, 0);
  lv_obj_set_style_radius(button, LV_RADIUS_CIRCLE, 0);
  lv_obj_set_style_border_width(button, 0, 0);
}
}
