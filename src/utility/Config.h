#ifndef _CONFIG_H_
#define _CONFIG_H_

#define M5_IR 9
#define M5_LED 10
#define M5_BUTTON_HOME 37
#define M5_BUTTON_RST 39

#define BUTTON_A_PIN 37
#define BUTTON_B_PIN 39

#ifdef M5STICKC_PLUS
#define BUZZER
#define BUZZER_ENABLE_PIN 2
#define BUZZER_TONE_PIN 0
#else

#endif

// UART
#define USE_SERIAL Serial

#endif /* SETTINGS_C */
