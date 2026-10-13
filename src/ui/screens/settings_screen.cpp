#include "settings_screen.h"
#include "app/screen_manager.h"
#include "ui/theme.h"
#include "ui/components/way_button.h"
namespace { void goHome(lv_event_t*) { wayline::ui::showScreen(wayline::ScreenId::Home); } }
lv_obj_t* createSettingsScreen() {
  lv_obj_t* s = lv_obj_create(nullptr); wayline::ui::theme::applyScreen(s);
  lv_obj_t* title = lv_label_create(s); lv_label_set_text(title, "CONFIGURACOES");
  wayline::ui::theme::applyTitle(title); lv_obj_align(title, LV_ALIGN_TOP_MID, 0, 20);
  const char* lines[] = {"Firmware: Wayline V1 / demo", "Display: AMOLED 466 x 466", "GPS: LC76G integrado", "Bluetooth: aguardando integracao", "Bateria: nao conectada"};
  for (uint8_t i = 0; i < 5; ++i) {
    lv_obj_t* label = lv_label_create(s); lv_label_set_text(label, lines[i]);
    wayline::ui::theme::applyMuted(label); lv_obj_align(label, LV_ALIGN_TOP_LEFT, 8, 86 + i * 34);
  }
  lv_obj_t* back = wayline::ui::components::createWayButton(s, "VOLTAR", goHome);
  lv_obj_align(back, LV_ALIGN_BOTTOM_MID, 0, -8); return s;
}
