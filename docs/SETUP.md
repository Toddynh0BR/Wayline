# Preparação e gravação

## Hardware conhecido

- Waveshare ESP32-S3-Touch-AMOLED-1.75-G com LC76G
- AMOLED CO5300 QSPI, 466×466; touch CST9217
- I²C compartilhado SDA GPIO15 / SCL GPIO14
- Ambiente local validado previamente: Arduino-ESP32 3.3.10, placa ESP32S3 Dev Module, Flash 16 MB e partição 16M Flash (3 MB APP / FATFS).

## Referências oficiais da placa

- Documentação: https://docs.waveshare.com/ESP32-S3-Touch-AMOLED-1.75
- Recursos: https://docs.waveshare.com/ESP32-S3-Touch-AMOLED-1.75/Resources-And-Documents
- Repositório da Waveshare: https://github.com/waveshareteam/ESP32-S3-Touch-AMOLED-1.75
- Exemplo Arduino LVGL: https://github.com/waveshareteam/ESP32-S3-Touch-AMOLED-1.75/tree/main/examples/arduino/06_LVGL_Widgets

## Estado deste commit

Este é o **esqueleto das telas e da arquitetura**; ainda não é um firmware pronto para gravar. O driver do display CO5300, buffers DMA, tick LVGL e touch CST9217 precisam ser integrados ao adaptador de hardware a partir do exemplo oficial, usando as bibliotecas `Arduino_GFX_Library.h`, `Arduino_CO5300`, `TouchDrvCSTXXX.hpp`, `pin_config.h` e `lv_conf.h` fornecidas no pacote Waveshare.

Isso é intencional: não vamos substituir o driver específico da placa por inicialização genérica presumida. O código das telas usa API LVGL 8, como no exemplo consultado. Antes de subir, confirme a versão real do LVGL/bibliotecas instaladas.

## Próximos passos

1. Integrar o adaptador oficial de display e touch.
2. Compilar com as bibliotecas concretas da placa.
3. Gravar e validar touch e navegação entre as cinco telas.
4. Conectar os estados reais do LC76G, IMU, RTC, AXP2101 e BLE.

Dados de GPS, bússola e rotas ainda são placeholders. Nenhuma navegação real está implementada.
