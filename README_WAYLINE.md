# Wayline V1 — firmware

Firmware inicial da placa **Waveshare ESP32-S3-Touch-AMOLED-1.75-G** (ESP32-S3, AMOLED circular 466×466 e GNSS LC76G).

> O branch `feat/initial-lvgl-ui` contém as telas LVGL e a organização da aplicação. O adaptador que inicializa fisicamente AMOLED e touch ainda precisa ser integrado do exemplo oficial. Portanto, este branch ainda não é firmware pronto para gravação.

## Organização

- `src/main.cpp`: bootstrap Arduino.
- `src/app/`: estado da aplicação e gerenciador de telas.
- `src/ui/screens/`: início, navegação, bússola, rotas e configurações.
- `src/ui/components/`: componentes reaproveitáveis.
- `src/ui/theme.*`: tema escuro com destaque vermelho.
- `src/hardware/`: ponto de integração dos drivers.
- `include/`: configuração conhecida e tipos do Wayline.
- `docs/SETUP.md`: instruções antes da gravação.

## Ambiente conhecido

O protótipo já foi validado no Arduino IDE com Arduino-ESP32 **3.3.10**, `ESP32S3 Dev Module`, Flash 16 MB e a partição usada no projeto `16M Flash (3MB APP / FATFS)`. O `platformio.ini` é apenas uma configuração inicial; as bibliotecas de display e touch precisam corresponder às versões do pacote Waveshare usado na placa.

## Documentação oficial

- https://docs.waveshare.com/ESP32-S3-Touch-AMOLED-1.75
- https://docs.waveshare.com/ESP32-S3-Touch-AMOLED-1.75/Resources-And-Documents
- https://github.com/waveshareteam/ESP32-S3-Touch-AMOLED-1.75
- Exemplo LVGL: https://github.com/waveshareteam/ESP32-S3-Touch-AMOLED-1.75/tree/main/examples/arduino/06_LVGL_Widgets

## Próximos passos

1. Integrar CO5300 QSPI, buffers LVGL, tick e touch CST9217 a partir do exemplo oficial.
2. Compilar com as bibliotecas instaladas e resolver diferenças de versão.
3. Gravar e validar touch + troca de telas.
4. Ligar estados reais de GPS, IMU, RTC, PMIC e BLE.

Os dados de GPS, bússola e rotas nas telas são demonstrativos; a navegação real ainda não está implementada.
