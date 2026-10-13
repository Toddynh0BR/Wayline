#include "navigation_screen.h"
#include "app/screen_manager.h"
#include "ui/theme.h"
#include "ui/components/way_button.h"
#include "ui/components/status_pill.h"
namespace { void goHome(lv_event_t*) { wayline::ui::showScreen(wayline::ScreenId::Home); }
void goCompass(lv_event_t*) { wayline::ui::showScreen(wayline::ScreenId::Compass); } }
lv_obj_t* createNavigationScreen() {
  lv_obj_t* s = lv_obj_create(nullptr); wayline::ui::theme::applyScreen(s);
  lv_obj_t* title = lv_label_create(s); lv_label_set_text(title, "NAVEGACAO");
  wayline::ui::theme::applyTitle(title); lv_obj_align(title, LV_ALIGN_TOP_MID, 0, 18);
  lv_obj_t* pill = wayline::ui::components::createStatusPill(s, "SEM ROTA ATIVA", false);
  lv_obj_align(pill, LV_ALIGN_TOP_MID, 0, 60);
  lv_obj_t* arrow = lv_label_create(s); lv_label_set_text(arrow, LV_SYMBOL_RIGHT);
  lv_obj_set_style_text_font(arrow, &lv_font_montserrat_48, 0);
  lv_obj_set_style_text_color(arrow, lv_color_hex(0xE53935), 0); lv_obj_align(arrow, LV_ALIGN_CENTER, 0, -28);
  lv_obj_t* hint = lv_label_create(s); lv_label_set_text(hint, "A rota sera enviada pelo aplicativo");
  wayline::ui::theme::applyMuted(hint); lv_obj_set_width(hint, 300); lv_label_set_long_mode(hint, LV_LABEL_LONG_WRAP);
  lv_obj_set_style_text_align(hint, LV_TEXT_ALIGN_CENTER, 0); lv_obj_align(hint, LV_ALIGN_CENTER, 0, 34);
  lv_obj_t* compass = wayline::ui::components::createWayButton(s, "ABRIR BUSSOLA", goCompass);
  lv_obj_align(compass, LV_ALIGN_CENTER, 0, 90);
  lv_obj_t* back = wayline::ui::components::createWayButton(s, "VOLTAR", goHome);
  lv_obj_align(back, LV_ALIGN_BOTTOM_MID, 0, -8); return s;
}
