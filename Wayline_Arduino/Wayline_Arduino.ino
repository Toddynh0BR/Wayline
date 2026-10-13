/*
 * WAYLINE V1 — base Arduino para Waveshare ESP32-S3-Touch-AMOLED-1.75-G
 * Arduino-ESP32 3.3.10 + LVGL 8.x + bibliotecas oficiais Waveshare.
 * GPS, rota real, BLE e heading calibrado sao integracoes futuras.
 */
#include <Arduino.h>
#include <Wire.h>
#include <lvgl.h>
#include <Arduino_GFX_Library.h>
#include <TouchDrvCSTXXX.hpp>
#include "pin_config.h"

static constexpr uint16_t C_WHITE=0xFFFF, C_MUTED=0x9CF3, C_RED=0xE986, C_YELLOW=0xFEA0;
Arduino_DataBus *displayBus = new Arduino_ESP32QSPI(LCD_CS,LCD_SCLK,LCD_SDIO0,LCD_SDIO1,LCD_SDIO2,LCD_SDIO3);
Arduino_GFX *display = new Arduino_CO5300(displayBus,LCD_RESET,0,LCD_WIDTH,LCD_HEIGHT,6,0,0,0);
TouchDrvCST92xx touch;
static lv_disp_draw_buf_t drawBuffer;
static lv_color_t *buffer1=nullptr, *buffer2=nullptr;
static esp_timer_handle_t tickTimer=nullptr;
static volatile bool touchInterrupt=false;
static int16_t touchX[5]={0}, touchY[5]={0};

enum class Page:uint8_t { Home,Navigation,Compass,Routes,Settings };
static Page currentPage=Page::Home;
static lv_obj_t *screens[5]={nullptr,nullptr,nullptr,nullptr,nullptr};
static uint8_t indexOf(Page p){return static_cast<uint8_t>(p);}
static void lvglTick(void*){lv_tick_inc(2);}
static void IRAM_ATTR onTouchInterrupt(){touchInterrupt=true;}

static void displayFlush(lv_disp_drv_t *driver,const lv_area_t *area,lv_color_t *colors){
  uint32_t w=area->x2-area->x1+1,h=area->y2-area->y1+1;
#if LV_COLOR_16_SWAP != 0
  display->draw16bitBeRGBBitmap(area->x1,area->y1,reinterpret_cast<uint16_t*>(&colors->full),w,h);
#else
  display->draw16bitRGBBitmap(area->x1,area->y1,reinterpret_cast<uint16_t*>(&colors->full),w,h);
#endif
  lv_disp_flush_ready(driver);
}
static void touchRead(lv_indev_drv_t*,lv_indev_data_t *data){
  if(!touchInterrupt){data->state=LV_INDEV_STATE_REL;return;}
  touchInterrupt=false;
  if(touch.getPoint(touchX,touchY,touch.getSupportTouchPoint())>0){
    data->state=LV_INDEV_STATE_PR;data->point.x=touchX[0];data->point.y=touchY[0];
  }else data->state=LV_INDEV_STATE_REL;
}
static void styleScreen(lv_obj_t*s){
  lv_obj_set_style_bg_color(s,lv_color_hex(0x08090C),LV_PART_MAIN);
  lv_obj_set_style_bg_opa(s,LV_OPA_COVER,LV_PART_MAIN);
  lv_obj_set_style_border_width(s,0,LV_PART_MAIN);lv_obj_set_style_pad_all(s,18,LV_PART_MAIN);
}
static lv_obj_t* label(lv_obj_t*p,const char*t,uint32_t color,const lv_font_t*f=&lv_font_montserrat_16){
  lv_obj_t*l=lv_label_create(p);lv_label_set_text(l,t);
  lv_obj_set_style_text_color(l,lv_color_hex(color),LV_PART_MAIN);
  lv_obj_set_style_text_font(l,f,LV_PART_MAIN);lv_label_set_long_mode(l,LV_LABEL_LONG_WRAP);return l;
}
static void goTo(Page p);
static void buttonEvent(lv_event_t*e){goTo(static_cast<Page>(reinterpret_cast<uintptr_t>(lv_event_get_user_data(e))));}
static lv_obj_t* button(lv_obj_t*p,const char*t,Page destination,bool primary=false){
  lv_obj_t*b=lv_btn_create(p);lv_obj_set_size(b,222,44);
  lv_obj_set_style_radius(b,16,LV_PART_MAIN);
  lv_obj_set_style_bg_color(b,lv_color_hex(primary?0xE53935:0x20232A),LV_PART_MAIN);
  lv_obj_set_style_bg_opa(b,LV_OPA_COVER,LV_PART_MAIN);
  lv_obj_set_style_border_width(b,1,LV_PART_MAIN);
  lv_obj_set_style_border_color(b,lv_color_hex(primary?0xE53935:0x3B3F48),LV_PART_MAIN);
  lv_obj_add_event_cb(b,buttonEvent,LV_EVENT_CLICKED,reinterpret_cast<void*>(static_cast<uintptr_t>(destination)));
  lv_obj_t*l=label(b,t,C_WHITE,&lv_font_montserrat_16);lv_obj_center(l);return b;
}
static void header(lv_obj_t*s,const char*t){lv_obj_t*l=label(s,t,C_WHITE,&lv_font_montserrat_28);lv_obj_align(l,LV_ALIGN_TOP_MID,0,14);}
static void createHome(){
  lv_obj_t*s=lv_obj_create(nullptr);screens[indexOf(Page::Home)]=s;styleScreen(s);
  lv_obj_t*brand=label(s,"WAYLINE",C_WHITE,&lv_font_montserrat_28);lv_obj_align(brand,LV_ALIGN_TOP_MID,0,18);
  lv_obj_t*sub=label(s,"MOTO NAVIGATION",C_MUTED,&lv_font_montserrat_14);
  lv_obj_set_style_text_letter_space(sub,3,LV_PART_MAIN);lv_obj_align(sub,LV_ALIGN_TOP_MID,0,53);
  lv_obj_t*status=lv_obj_create(s);lv_obj_set_size(status,210,30);
  lv_obj_set_style_radius(status,15,LV_PART_MAIN);lv_obj_set_style_bg_color(status,lv_color_hex(0x252014),LV_PART_MAIN);
  lv_obj_set_style_border_color(status,lv_color_hex(0x7A5D1A),LV_PART_MAIN);lv_obj_align(status,LV_ALIGN_TOP_MID,0,78);
  lv_obj_t*st=label(status,"GPS  |  AGUARDANDO",C_YELLOW,&lv_font_montserrat_14);lv_obj_center(st);
  lv_obj_t*n=button(s,"INICIAR NAVEGACAO",Page::Navigation,true);lv_obj_align(n,LV_ALIGN_CENTER,0,-24);
  lv_obj_t*c=button(s,"BUSSOLA",Page::Compass);lv_obj_align(c,LV_ALIGN_CENTER,0,28);
  lv_obj_t*r=button(s,"ROTAS SALVAS",Page::Routes);lv_obj_align(r,LV_ALIGN_CENTER,0,80);
  lv_obj_t*cfg=label(s,"CONFIGURACOES  >",C_MUTED,&lv_font_montserrat_14);
  lv_obj_add_flag(cfg,LV_OBJ_FLAG_CLICKABLE);lv_obj_add_event_cb(cfg,buttonEvent,LV_EVENT_CLICKED,reinterpret_cast<void*>(static_cast<uintptr_t>(Page::Settings)));
  lv_obj_align(cfg,LV_ALIGN_BOTTOM_MID,0,-5);
}
static void createNavigation(){
  lv_obj_t*s=lv_obj_create(nullptr);screens[indexOf(Page::Navigation)]=s;styleScreen(s);header(s,"NAVEGACAO");
  lv_obj_t*pill=lv_obj_create(s);lv_obj_set_size(pill,200,30);lv_obj_set_style_radius(pill,15,LV_PART_MAIN);
  lv_obj_set_style_bg_color(pill,lv_color_hex(0x252014),LV_PART_MAIN);lv_obj_set_style_border_color(pill,lv_color_hex(0x7A5D1A),LV_PART_MAIN);
  lv_obj_align(pill,LV_ALIGN_TOP_MID,0,56);lv_obj_t*pt=label(pill,"SEM ROTA ATIVA",C_YELLOW,&lv_font_montserrat_14);lv_obj_center(pt);
  lv_obj_t*a=label(s,LV_SYMBOL_RIGHT,C_RED,&lv_font_montserrat_48);lv_obj_align(a,LV_ALIGN_CENTER,0,-45);
  lv_obj_t*msg=label(s,"Aguardando rota enviada pelo aplicativo",C_MUTED,&lv_font_montserrat_16);
  lv_obj_set_width(msg,280);lv_obj_set_style_text_align(msg,LV_TEXT_ALIGN_CENTER,LV_PART_MAIN);lv_obj_align(msg,LV_ALIGN_CENTER,0,20);
  lv_obj_t*hint=label(s,"A rota sera transferida do celular por Bluetooth.",C_MUTED,&lv_font_montserrat_14);
  lv_obj_set_width(hint,280);lv_obj_set_style_text_align(hint,LV_TEXT_ALIGN_CENTER,LV_PART_MAIN);lv_obj_align(hint,LV_ALIGN_CENTER,0,62);
  lv_obj_t*b=button(s,"VOLTAR",Page::Home);lv_obj_align(b,LV_ALIGN_BOTTOM_MID,0,-2);
}
static void createCompass(){
  lv_obj_t*s=lv_obj_create(nullptr);screens[indexOf(Page::Compass)]=s;styleScreen(s);header(s,"BUSSOLA");
  lv_obj_t*a=lv_arc_create(s);lv_obj_set_size(a,220,220);lv_arc_set_bg_angles(a,0,360);lv_arc_set_angles(a,30,330);
  lv_obj_set_style_arc_color(a,lv_color_hex(0x343842),LV_PART_MAIN);lv_obj_set_style_arc_width(a,10,LV_PART_MAIN);
  lv_obj_set_style_arc_color(a,lv_color_hex(0xE53935),LV_PART_INDICATOR);lv_obj_set_style_arc_width(a,10,LV_PART_INDICATOR);
  lv_obj_set_style_bg_opa(a,LV_OPA_TRANSP,LV_PART_KNOB);lv_obj_clear_flag(a,LV_OBJ_FLAG_CLICKABLE);lv_obj_align(a,LV_ALIGN_CENTER,0,-15);
  lv_obj_t*n=label(s,LV_SYMBOL_UP,C_RED,&lv_font_montserrat_48);lv_obj_align(n,LV_ALIGN_CENTER,0,-25);
  lv_obj_t*h=label(s,"N -- deg",C_WHITE,&lv_font_montserrat_20);lv_obj_align(h,LV_ALIGN_CENTER,0,28);
  lv_obj_t*note=label(s,"Heading real sera ativado apos integrar e calibrar os sensores.",C_MUTED,&lv_font_montserrat_14);
  lv_obj_set_width(note,280);lv_obj_set_style_text_align(note,LV_TEXT_ALIGN_CENTER,LV_PART_MAIN);lv_obj_align(note,LV_ALIGN_CENTER,0,105);
  lv_obj_t*b=button(s,"VOLTAR",Page::Home);lv_obj_align(b,LV_ALIGN_BOTTOM_MID,0,-2);
}
static void createRoutes(){
  lv_obj_t*s=lv_obj_create(nullptr);screens[indexOf(Page::Routes)]=s;styleScreen(s);header(s,"ROTAS SALVAS");
  lv_obj_t*i=label(s,LV_SYMBOL_GPS,C_RED,&lv_font_montserrat_48);lv_obj_align(i,LV_ALIGN_CENTER,0,-60);
  lv_obj_t*empty=label(s,"Nenhuma rota sincronizada ainda.",C_WHITE,&lv_font_montserrat_16);
  lv_obj_set_width(empty,270);lv_obj_set_style_text_align(empty,LV_TEXT_ALIGN_CENTER,LV_PART_MAIN);lv_obj_align(empty,LV_ALIGN_CENTER,0,2);
  lv_obj_t*detail=label(s,"Quando o app enviar uma rota, ela aparecera aqui.",C_MUTED,&lv_font_montserrat_14);
  lv_obj_set_width(detail,270);lv_obj_set_style_text_align(detail,LV_TEXT_ALIGN_CENTER,LV_PART_MAIN);lv_obj_align(detail,LV_ALIGN_CENTER,0,45);
  lv_obj_t*b=button(s,"VOLTAR",Page::Home);lv_obj_align(b,LV_ALIGN_BOTTOM_MID,0,-2);
}
static void createSettings(){
  lv_obj_t*s=lv_obj_create(nullptr);screens[indexOf(Page::Settings)]=s;styleScreen(s);header(s,"CONFIGURACOES");
  const char*items[]={"Firmware: Wayline V1 (base)","Tela: AMOLED 466 x 466","Touch: CST9217","GPS: LC76G / pendente","Bluetooth: integracao pendente","Bateria: leitura pendente"};
  for(uint8_t i=0;i<sizeof(items)/sizeof(items[0]);i++){
    lv_obj_t*r=lv_obj_create(s);lv_obj_set_size(r,285,32);lv_obj_set_style_bg_color(r,lv_color_hex(0x17191F),LV_PART_MAIN);
    lv_obj_set_style_bg_opa(r,LV_OPA_COVER,LV_PART_MAIN);lv_obj_set_style_border_width(r,0,LV_PART_MAIN);lv_obj_set_style_radius(r,8,LV_PART_MAIN);
    lv_obj_align(r,LV_ALIGN_TOP_MID,0,64+i*36);lv_obj_t*t=label(r,items[i],C_MUTED,&lv_font_montserrat_14);lv_obj_align(t,LV_ALIGN_LEFT_MID,6,0);
  }
  lv_obj_t*b=button(s,"VOLTAR",Page::Home);lv_obj_align(b,LV_ALIGN_BOTTOM_MID,0,-2);
}
static void goTo(Page p){uint8_t i=indexOf(p);if(i>=5||!screens[i])return;currentPage=p;lv_scr_load(screens[i]);Serial.printf("[UI] tela=%u\n",i);}

static bool initializeDisplayAndLvgl(){
  if(!display->begin()){Serial.println("[DISPLAY] falha CO5300");return false;}
  display->setBrightness(180);lv_init();
  const size_t pixels=(LCD_WIDTH*LCD_HEIGHT)/10;
  buffer1=static_cast<lv_color_t*>(heap_caps_malloc(pixels*sizeof(lv_color_t),MALLOC_CAP_DMA));
  buffer2=static_cast<lv_color_t*>(heap_caps_malloc(pixels*sizeof(lv_color_t),MALLOC_CAP_DMA));
  if(!buffer1||!buffer2){Serial.println("[LVGL] memoria DMA insuficiente");return false;}
  lv_disp_draw_buf_init(&drawBuffer,buffer1,buffer2,pixels);
  static lv_disp_drv_t dd;lv_disp_drv_init(&dd);dd.hor_res=LCD_WIDTH;dd.ver_res=LCD_HEIGHT;dd.flush_cb=displayFlush;dd.draw_buf=&drawBuffer;lv_disp_drv_register(&dd);
  static lv_indev_drv_t id;lv_indev_drv_init(&id);id.type=LV_INDEV_TYPE_POINTER;id.read_cb=touchRead;lv_indev_drv_register(&id);
  const esp_timer_create_args_t args={.callback=&lvglTick,.arg=nullptr,.dispatch_method=ESP_TIMER_TASK,.name="wayline_lvgl_tick",.skip_unhandled_events=true};
  if(esp_timer_create(&args,&tickTimer)==ESP_OK)esp_timer_start_periodic(tickTimer,2000);
  return true;
}
static void initializeTouch(){
  pinMode(TP_RESET,OUTPUT);digitalWrite(TP_RESET,LOW);delay(30);digitalWrite(TP_RESET,HIGH);delay(80);
  touch.setPins(TP_RESET,TP_INT);
  if(!touch.begin(Wire,0x5A,IIC_SDA,IIC_SCL)){Serial.println("[TOUCH] CST9217 nao respondeu");return;}
  touch.setMaxCoordinates(LCD_WIDTH,LCD_HEIGHT);touch.setMirrorXY(true,true);pinMode(TP_INT,INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(TP_INT),onTouchInterrupt,FALLING);
  Serial.printf("[TOUCH] %s inicializado\n",touch.getModelName());
}
void setup(){
  Serial.begin(115200);delay(300);Serial.println("\nWAYLINE V1 - firmware Arduino");
  Wire.begin(IIC_SDA,IIC_SCL);Wire.setClock(400000);initializeTouch();
  if(!initializeDisplayAndLvgl()){Serial.println("[FATAL] confira bibliotecas e configuracao");while(true)delay(1000);}
  createHome();createNavigation();createCompass();createRoutes();createSettings();goTo(Page::Home);
  Serial.println("[WAYLINE] telas prontas; GPS, BLE e rota sao placeholders.");
}
void loop(){lv_timer_handler();delay(5);}
