# Wayline V1 — firmware Arduino IDE

Esta pasta contém um sketch Arduino para a Waveshare ESP32-S3-Touch-AMOLED-1.75-G. Inicializa o display CO5300 por QSPI, o touch CST9217 por I²C e LVGL 8, com cinco telas navegáveis.

## Abrir e gravar

1. Abra o arquivo Wayline_Arduino.ino no Arduino IDE.
2. Adicione as bibliotecas do pacote oficial Waveshare, em especial Arduino_GFX_Library, lvgl 8.x e a biblioteca que fornece TouchDrvCSTXXX.hpp. As versões oficiais ficam em [examples/arduino/libraries](https://github.com/waveshareteam/ESP32-S3-Touch-AMOLED-1.75/tree/main/examples/arduino/libraries).
3. Mantenha Wayline_Arduino.ino, pin_config.h e lv_conf.h na mesma pasta.
4. Placa: ESP32S3 Dev Module. Flash: 16MB. PSRAM: OPI PSRAM, se disponível. Partição: 16M Flash (3MB APP/9.9MB FATFS) / app3M_fat9M_16MB.
5. Selecione a porta da placa, grave e abra o monitor serial em 115200.

## Telas

- Início: atalhos e status GPS demonstrativo.
- Navegação: indicação visual de próxima manobra, aguardando uma rota.
- Bússola: mostrador de interface, sem heading real ainda.
- Rotas salvas: estado vazio até a integração com o aplicativo.
- Configurações: informações de hardware e integrações pendentes.

## O que falta

O firmware de interface foi escrito com base nos exemplos oficiais da Waveshare. GPS LC76G, BLE, leitura real da bateria e heading calibrado ainda não foram integrados. Estados com “pendente” são intencionais, não leituras reais. A compilação precisa ser validada localmente com as bibliotecas oficiais instaladas.

Referências: [documentação da placa](https://docs.waveshare.com/ESP32-S3-Touch-AMOLED-1.75), [exemplo oficial LVGL](https://github.com/waveshareteam/ESP32-S3-Touch-AMOLED-1.75/blob/main/examples/arduino/06_LVGL_Widgets/06_LVGL_Widgets.ino), [bibliotecas oficiais](https://github.com/waveshareteam/ESP32-S3-Touch-AMOLED-1.75/tree/main/examples/arduino/libraries), [página do AliExpress da placa](https://pt.aliexpress.com/item/1005008985857452.html?utm_source=chatgpt.com).
