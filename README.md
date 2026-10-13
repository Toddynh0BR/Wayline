# Wayline — firmware

Firmware inicial do Wayline V1 para a placa **Waveshare ESP32-S3-Touch-AMOLED-1.75-G** (AMOLED circular 466×466, ESP32-S3, Arduino-ESP32 3.3.10).

> Esta primeira versão é um esqueleto de interface: as telas e navegação LVGL são reais; GPS, bússola, rotas, BLE e estado da bateria ainda são placeholders até integrarmos os respectivos drivers e protocolos.

## Ambiente alvo

- Arduino IDE
- Arduino-ESP32 **3.3.10**
- Placa: `ESP32S3 Dev Module`
- Flash: `16MB`
- Partição: `app3M_fat9M_16MB` (nome equivalente à opção 16M Flash / 3MB APP / FATFS no IDE usado no projeto)
- Placa: Waveshare ESP32-S3-Touch-AMOLED-1.75-G, LC76G GNSS integrado

A implementação de display/touch deve manter compatibilidade com as bibliotecas e configurações fornecidas no pacote oficial da Waveshare para esta placa. Veja `docs/SETUP.md`.

## Estrutura

```text
Wayline/
├── include/
│   ├── board_config.h
│   └── wayline_types.h
├── src/
│   ├── main.cpp
│   ├── app/
│   │   ├── app_state.h
│   │   ├── app_state.cpp
│   │   ├── screen_manager.h
│   │   └── screen_manager.cpp
│   ├── ui/
│   │   ├── theme.h
│   │   ├── theme.cpp
│   │   ├── components/
│   │   │   ├── way_button.h/.cpp
│   │   │   └── status_pill.h/.cpp
│   │   └── screens/
│   │       ├── home_screen.h/.cpp
│   │       ├── navigation_screen.h/.cpp
│   │       ├── compass_screen.h/.cpp
│   │       ├── routes_screen.h/.cpp
│   │       └── settings_screen.h/.cpp
│   └── hardware/
│       └── hardware_status.h/.cpp
└── docs/
    └── SETUP.md
```

## Estado atual

- [x] Esqueleto LVGL com tela inicial e navegação entre páginas
- [x] Componentes reutilizáveis e tema Wayline escuro/vermelho
- [x] Telas de navegação, bússola, rotas e configurações com dados demonstrativos
- [ ] Integração final do driver AMOLED e CST9217 touch com as bibliotecas da placa
- [ ] GNSS LC76G ligado ao estado de navegação
- [ ] BLE entre app mobile e Wayline
- [ ] Persistência de rotas
- [ ] Sensores e gerenciamento de energia

## Documentação oficial consultada

- Placa e documentação: https://docs.waveshare.com/ESP32-S3-Touch-AMOLED-1.75
- Recursos/documentos: https://docs.waveshare.com/ESP32-S3-Touch-AMOLED-1.75/Resources-And-Documents
- Repositório oficial: https://github.com/waveshareteam/ESP32-S3-Touch-AMOLED-1.75
- Exemplo LVGL oficial: https://github.com/waveshareteam/ESP32-S3-Touch-AMOLED-1.75/tree/main/examples/arduino/06_LVGL_Widgets
- Exemplo LC76G I²C: https://github.com/waveshareteam/ESP32-S3-Touch-AMOLED-1.75/tree/main/examples/arduino/09_LC76G_I2C
