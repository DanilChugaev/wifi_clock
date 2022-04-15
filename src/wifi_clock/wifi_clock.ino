/*
 * Скетч к проекту "WI-FI часы"
 * Исходники на Github https://github.com/DanilChugaev/wifi_clock
 * Автор проекта Данил Чугаев
 */

// ============= НАСТРОЙКИ =============
// -------- ВРЕМЯ -------
#define GMT 7                                 // текущий часовой пояс (Красноярск 7)
#define TIME_SHIFT -4                         // смещение времени, относительно текущего (Красноярск 7 - 4 = Москва)
#define NTP_ADDRESS  "europe.pool.ntp.org"    // сервер времени
#define NTP_INTERVAL 60 * 60 * 1000           // обновление времени с сервера (1 час)
#define DISPLAY_INTERVAL 200                 // обновление времени на дисплее (0.2 секунды)

// -------- Менеджер WiFi ---------
#define AC_SSID "TP-Link_BCEB"
#define AC_PASS "21285967"
#define AP_PORT 8899

// -------- МАТРИЦА ---------
#define BRIGHTNESS 5         // стандартная маскимальная яркость (0-255)
#define CURRENT_LIMIT 2000    // лимит по току в миллиамперах, автоматически управляет яркостью

#define COLOR_ORDER GRB       // порядок цветов на ленте

#define WIDTH 18              // ширина матрицы
#define HEIGHT 14             // высота матрицы

#define NUM_LEDS WIDTH * HEIGHT
#define LED_PIN D4            // пин ленты
// ---------------- БИБЛИОТЕКИ -----------------
#include "microDS3231.h"  // https://alexgyver.ru/microlibs/ + https://github.com/AlexGyver/GyverLibs/tree/master/microDS3231
#include <WiFiManager.h>  // https://github.com/tzapu/WiFiManager/tree/0.16.0
#include <WiFiUdp.h>
#include <NTPClient.h>
#include <FastLED.h>      // https://github.com/FastLED/FastLED
#include <EncButton2.h>   // https://github.com/GyverLibs/EncButton

#include "timer.h"
#include "clock.h"

// ------------------- ТИПЫ --------------------
CRGB leds[NUM_LEDS];
WiFiManager wifiManager;
WiFiUDP Udp;
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, NTP_ADDRESS, GMT * 3600, NTP_INTERVAL);

timer refreshTimeTimer(NTP_INTERVAL);
timer refreshLEDTimer(DISPLAY_INTERVAL);

MegaClock nskClock(leds, 1, 8, 0, CRGB(0, 255, 0));
MegaClock mskClock(leds, 1, 1, TIME_SHIFT, CRGB(0, 0, 255));

EncButton2<EB_ENCBTN> enc(INPUT, D7, D6, D5); // https://github.com/GyverLibs/EncButton/blob/main/examples/EncButton2/EncButton2.ino

// ----------------- ПЕРЕМЕННЫЕ ----------------
String clock_ip = "";
unsigned int localPort = AP_PORT;
unsigned int brightness = 2;  // яркость светодиодов
unsigned int increase = 20;   // на это число умножаем сглаженное значение яркости, чтобы выровнять до нормальных значений яркости светодиодов
unsigned int smoothing = 50; // делим на это число, чтобы сгладить колебания итоговой яркости с датчика
unsigned int increase = 10;   // на это число умножаем сглаженное значение яркости, чтобы выровнять до нормальных значений яркости светодиодов
byte hrs, mins, secs;
byte days;

// для обновления времени в rtc
DateTime rtcNow;

unsigned int encoderValue = 0;

void setup() {
  Serial.begin(115200);

  initialLED();
  connectToWiFi();

//  Serial.printf("UDP server on port %d\n", localPort);
  Udp.begin(localPort);

  timeClient.begin();
  updateDateTime();
}

void loop() {
  enc.tick();

  if (enc.left() && encoderValue >= 5) {
    encoderValue = encoderValue - 5;
  }
  
  if (enc.right() && encoderValue < 255) {
    encoderValue = encoderValue + 5;
  }
  
  /**
   * Обновляем время с сервера у модуля часов,
   * когда пройдет NTP_INTERVAL, с момента последнего обновления
   */
  if (refreshTimeTimer.isReady()) {
    updateDateTime();
  }

  /**
   * Обновляем дисплей,
   * когда пройдет DISPLAY_INTERVAL, с момента последнего обновления
   */
  if (refreshLEDTimer.isReady()) {
    FastLED.clear();

    nskClock.update();
    mskClock.update();
    updateBrightness();
  
    FastLED.show();
  }
}
