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
#define NTP_INTERVAL 60 * 60 * 1000           // обновление времени с сервера (1 час)
#define DISPLAY_INTERVAL 1000                 // обновление времени на дисплее (1 секунда)

// -------- Менеджер WiFi ---------
#define AC_SSID "WiFi_Clock"
#define AC_PASS "time_to_sleep"
#define AP_PORT 8899

// -------- МАТРИЦА ---------
#define BRIGHTNESS 40         // стандартная маскимальная яркость (0-255)
#define CURRENT_LIMIT 2000    // лимит по току в миллиамперах, автоматически управляет яркостью

#define COLOR_ORDER RGB       // порядок цветов на ленте
#define MATRIX_TYPE 0         // тип матрицы: 0 - зигзаг, 1 - параллельная
#define CONNECTION_ANGLE 0    // угол подключения: 0 - левый нижний, 1 - левый верхний, 2 - правый верхний, 3 - правый нижний
#define STRIP_DIRECTION 0     // направление ленты из угла: 0 - вправо, 1 - вверх, 2 - влево, 3 - вниз

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

// ------------------- ТИПЫ --------------------
CRGB leds[NUM_LEDS];
MicroDS3231 rtc;
WiFiManager wifiManager;
WiFiUDP Udp;
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, NTP_ADDRESS, GMT * 3600, NTP_INTERVAL);

timer refreshTimer(NTP_INTERVAL);

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
  // обновляем время с сервера у модуля часов,
  // когда пройдет NTP_INTERVAL, с момента последнего обновления
  if (refreshTimer.isReady()) {
    updateDateTime();
  }

  delay(100);
  
//  Serial.println(getBrightness());

//  leds[1] = CHSV(0, 255, 0);
  leds[0] = CHSV(random(0, 255), 255, 255); FastLED.show(); delay(30);
//  leds[0] = CRGB::Black; FastLED.show(); delay(30);
}
