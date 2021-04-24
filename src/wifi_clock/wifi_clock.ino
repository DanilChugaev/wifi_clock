/*
 * Скетч к проекту "WI-FI часы"
 * Исходники на Github https://github.com/DanilChugaev/wifi_clock
 * Автор проекта Данил Чугаев
 */

// TODO: схему проекта поместить в корень проекта
// TODO: описать редми
// TODO: приложение для андроид (исходники и .apk файл возможно и ios), 
//   сделанное в https://thunkable.com, поместить в android (ios) папку в корень проекта

// ============= НАСТРОЙКИ =============

// -------- ВРЕМЯ -------
#define GMT 7                                 // текущий часовой пояс (Красноярск 7)
#define TIME_SHIFT -4                         // смещение времени, относительно текущего (Красноярск 7 - 4 = Москва)
#define NTP_ADDRESS  "europe.pool.ntp.org"    // сервер времени
#define NTP_INTERVAL 60 * 60 * 1000   // обновление времени с сервера (1 час)
#define DISPLAY_INTERVAL 1000              // обновление времени на дисплее (1 секунда)

// -------- Менеджер WiFi ---------
#define AC_SSID "WiFi_Clock"
#define AC_PASS "time_to_sleep"

// ---------------- БИБЛИОТЕКИ -----------------
#include "microDS3231.h" // https://alexgyver.ru/microlibs/ + https://github.com/AlexGyver/GyverLibs/tree/master/microDS3231
#include <WiFiManager.h> // https://github.com/tzapu/WiFiManager/tree/0.16.0

// ------------------- ТИПЫ --------------------
MicroDS3231 rtc;
WiFiManager wifiManager;

// ----------------- ПЕРЕМЕННЫЕ ----------------
boolean internet_connected = false;
String clock_ip = "";

void setup() {
  Serial.begin(115200);

  connectToWiFi();
}

void loop() {
//  printTime();
  delay(1000);
}
