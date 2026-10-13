#include "home_screen.h"
#include "app/screen_manager.h"
#include "ui/theme.h"
#include "ui/components/way_button.h"
#include "ui/components/status_pill.h"
namespace {
void openNavigation(lv_event_t*) { wayline::ui::showScreen(wayline::ScreenId::Navigation); }
void openCompass(lv_event_t*) { wayline::ui::showScreen(wayline::ScreenId::Compass); }
void openRoutes(lv_event_t*) { wayline::ui::showScreen(wayline::ScreenId::Routes); }
void openSettings(lv_event_t*) { wayline::ui::showScreen(wayline::ScreenId::Settings); }
}
lv_obj_t* createHomeScreen() {
  lv_obj_t* s = lv_obj_create(nullptr); wayline::ui::theme::applyScreen(s);
  lv_obj_t* brand = lv_label_create(s); lv_label_set_text(brand, "WAYLINE");
  wayline::ui::theme::applyTitle(brand); lv_obj_align(brand, LV_ALIGN_TOP_MID, 0, 22);
  lv_obj_t* subtitle = lv_label_create(s); lv_label_set_text(subtitle, "MOTO NAVIGATION");
  wayline::ui::theme::applyMuted(subtitle); lv_obj_set_style_text_letter_space(subtitle, 3, 0);
  lv_obj_align(subtitle, LV_ALIGN_TOP_MID, 0, 58);
  lv_obj_t* pill = wayline::ui::components::createStatusPill(s, "DEMO | GPS PENDENTE", false);
  lv_obj_align(pill, LV_ALIGN_TOP_MID, 0, 88);
  lv_obj_t* nav = wayline::ui::components::createWayButton(s, "INICIAR NAVEGACAO", openNavigation);
  lv_obj_align(nav, LV_ALIGN_CENTER, 0, -42);
  lv_obj_t* compass = wayline::ui::components::createWayButton(s, "BUSSOLA", openCompass);
  lv_obj_align(compass, LV_ALIGN_CENTER, 0, 14);
  lv_obj_t* routes = wayline::ui::components::createWayButton(s, "ROTAS SALVAS", openRoutes);
  lv_obj_align(routes, LV_ALIGN_CENTER, 0, 70);
  lv_obj_t* settings = lv_label_create(s); lv_label_set_text(settings, "CONFIGURACOES  >");
  wayline::ui::theme::applyMuted(settings); lv_obj_align(settings, LV_ALIGN_BOTTOM_MID, 0, -18);
  lv_obj_add_flag(settings, LV_OBJ_FLAG_CLICKABLE);
  lv_obj_add_event_cb(settings, openSettings, LV_EVENT_CLICKED, nullptr);
  return s;
}
