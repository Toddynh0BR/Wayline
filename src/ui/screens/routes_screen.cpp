#include "routes_screen.h"
#include "app/screen_manager.h"
#include "ui/theme.h"
#include "ui/components/way_button.h"
namespace { void goHome(lv_event_t*) { wayline::ui::showScreen(wayline::ScreenId::Home); } }
lv_obj_t* createRoutesScreen() {
  lv_obj_t* s = lv_obj_create(nullptr); wayline::ui::theme::applyScreen(s);
  lv_obj_t* title = lv_label_create(s); lv_label_set_text(title, "ROTAS SALVAS");
  wayline::ui::theme::applyTitle(title); lv_obj_align(title, LV_ALIGN_TOP_MID, 0, 22);
  lv_obj_t* empty = lv_label_create(s);
  lv_label_set_text(empty, "Nenhuma rota recebida ainda.\\n\\nQuando o app enviar uma rota,\\nela aparecera aqui.");
  wayline::ui::theme::applyMuted(empty); lv_obj_set_style_text_align(empty, LV_TEXT_ALIGN_CENTER, 0);
  lv_obj_align(empty, LV_ALIGN_CENTER, 0, -5);
  lv_obj_t* back = wayline::ui::components::createWayButton(s, "VOLTAR", goHome);
  lv_obj_align(back, LV_ALIGN_BOTTOM_MID, 0, -8); return s;
}
