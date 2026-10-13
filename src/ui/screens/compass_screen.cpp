#include "compass_screen.h"
#include "app/screen_manager.h"
#include "ui/theme.h"
#include "ui/components/way_button.h"
#include "ui/components/status_pill.h"
namespace { void goHome(lv_event_t*) { wayline::ui::showScreen(wayline::ScreenId::Home); } }
lv_obj_t* createCompassScreen() {
  lv_obj_t* s = lv_obj_create(nullptr); wayline::ui::theme::applyScreen(s);
  lv_obj_t* title = lv_label_create(s); lv_label_set_text(title, "BUSSOLA");
  wayline::ui::theme::applyTitle(title); lv_obj_align(title, LV_ALIGN_TOP_MID, 0, 20);
  lv_obj_t* pill = wayline::ui::components::createStatusPill(s, "AGUARDANDO IMU", false);
  lv_obj_align(pill, LV_ALIGN_TOP_MID, 0, 62);
  lv_obj_t* ring = lv_arc_create(s); lv_obj_set_size(ring, 230, 230);
  lv_arc_set_bg_angles(ring, 0, 360); lv_arc_set_angles(ring, 25, 335);
  lv_obj_set_style_arc_color(ring, lv_color_hex(0x3B3B46), LV_PART_MAIN);
  lv_obj_set_style_arc_width(ring, 9, LV_PART_MAIN);
  lv_obj_set_style_arc_color(ring, lv_color_hex(0xE53935), LV_PART_INDICATOR);
  lv_obj_set_style_arc_width(ring, 9, LV_PART_INDICATOR);
  lv_obj_clear_flag(ring, LV_OBJ_FLAG_CLICKABLE); lv_obj_align(ring, LV_ALIGN_CENTER, 0, -4);
  lv_obj_t* north = lv_label_create(s); lv_label_set_text(north, LV_SYMBOL_UP);
  lv_obj_set_style_text_font(north, &lv_font_montserrat_48, 0);
  lv_obj_set_style_text_color(north, lv_color_hex(0xE53935), 0); lv_obj_align(north, LV_ALIGN_CENTER, 0, -12);
  lv_obj_t* note = lv_label_create(s); lv_label_set_text(note, "Sem orientacao calibrada");
  wayline::ui::theme::applyMuted(note); lv_obj_align(note, LV_ALIGN_CENTER, 0, 52);
  lv_obj_t* back = wayline::ui::components::createWayButton(s, "VOLTAR", goHome);
  lv_obj_align(back, LV_ALIGN_BOTTOM_MID, 0, -8); return s;
}
