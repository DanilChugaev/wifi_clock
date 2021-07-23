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
#define DISPLAY_INTERVAL 1000                 // обновление времени на дисплее (1 секунда)

// -------- Менеджер WiFi ---------
#define AC_SSID "WiFi_Clock"
#define AC_PASS "time_to_sleep"
#define AP_PORT 8899

// -------- МАТРИЦА ---------
#define BRIGHTNESS 20         // стандартная маскимальная яркость (0-255)
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

#include "timer.h"
#include "clock.h"

// ------------------- ТИПЫ --------------------
CRGB leds[NUM_LEDS];
MicroDS3231 rtc;
WiFiManager wifiManager;
WiFiUDP Udp;
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, NTP_ADDRESS, GMT * 3600, NTP_INTERVAL);

timer refreshTimer(NTP_INTERVAL);
MegaClock nskClock(leds, 1, 1, 0, CRGB(0, 255, 0));
//MegaClock mskClock(leds, 1, 1, -4);

// ----------------- ПЕРЕМЕННЫЕ ----------------
//boolean internet_connected = false;
String clock_ip = "";
unsigned int localPort = AP_PORT;
unsigned int brightness; // яркость светодиодов
byte hrs, mins, secs;
byte days;

void setup() {
  Serial.begin(115200);

  initialLED();

  connectToWiFi();

  Serial.printf("UDP server on port %d\n", localPort);
  Udp.begin(localPort);

  timeClient.begin();

  updateDateTime();
}

void loop() {
  /**
   * Обновляем время с сервера у модуля часов,
   * когда пройдет NTP_INTERVAL, с момента последнего обновления
   */
  if (refreshTimer.isReady()) {
    updateDateTime();
  }

  DateTime now = rtc.getTime();
  nskClock.update(now);
//  mskClock.update(now);

  FastLED.show();

  delay(100);
  
//  Serial.println(getBrightness());

//  leds[1] = CHSV(0, 255, 0);
//  for (int i = 0; i < NUM_LEDS; i++) {
//    leds[i] = CRGB(0, 0, 255);
//    FastLED.show();
//    delay(300);
//  }
//  leds[getPosition(0, 1)] = CRGB(0, 255, 0);
//  leds[getPosition(0, 2)] = CRGB(255, 255, 0);
//  leds[getPosition(1, 2)] = CRGB(255, 255, 0);
//  FastLED.show();
}
