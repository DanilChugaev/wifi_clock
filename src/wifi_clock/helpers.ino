/*
 * Просто коннектится к вай-фаю
 * 
 * @global_var clock_ip
 * @global_var AC_SSID
 * @global_var AC_PASS
 * 
 * @global_class wifiManager
 * @global_class WiFi
 *
 * @return {void}
 */
void connectToWiFi() {
  wifiManager.setDebugOutput(true);

  wifiManager.autoConnect(AC_SSID, AC_PASS);
  clock_ip = WiFi.localIP().toString();
}

/*
 * Возвращает местоположение светодиода по указанным координатам
 * Нечетные полосы (начиная от 0 светодиода) идут вниз
 * Четные идут вверх
 * 
 * @global_var HEIGHT
 * 
 * @param {int8_t} x - позиция по оси `x`
 * @param {int8_t} y - позиция по оси `y`
 *
 * @return {uint16_t}
 */
uint16_t getPosition(int8_t x, int8_t y) {
  return x % 2 != 0 ? x * HEIGHT + y : x * HEIGHT + (HEIGHT - 1) - y;
}

/*
 * Получает значение с датчика освещенности
 * 
 * @global_var A0
 * 
 * @global_func analogRead
 * 
 * @return {unsigned int}
 */
unsigned int getBrightness() {
  return analogRead(A0);
}

/*
 * Инициализирует ленту
 * 
 * @global_var WS2812B
 * @global_var LED_PIN
 * @global_var COLOR_ORDER
 * @global_var leds
 * @global_var NUM_LEDS

 * @global_var CURRENT_LIMIT
 * 
 * @global_class FastLED
 * 
 * @return {void}
 */
void initialLED() {
  FastLED.addLeds<WS2812B, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS);
  updateBrightness();
  
  if (CURRENT_LIMIT > 0) FastLED.setMaxPowerInVoltsAndMilliamps(5, CURRENT_LIMIT);
  
  FastLED.show();
}

/*
 * Обновляет яркость светодиодов
 *
 * @global_var brightness
 */
void updateBrightness() {
  brightness = int(floor(getBrightness() / smoothing)) * increase;
  
  Serial.println(brightness);

  FastLED.setBrightness(brightness);
}

/*
 * Обновляет время из интернета
 * Формат передачи в setTime - SEC, MIN, HOUR, DAY, MONTH, YEAR
 * 
 * @global_var WL_CONNECTED
 * 
 * @global_class rtc
 * @global_class DateTime
 * @global_class WiFi
 * @global_class timeClient
 * 
 * @return {void}
 */
void updateDateTime() {
  if (WiFi.status() == WL_CONNECTED) {
    if (timeClient.update()) {
      hrs = timeClient.getHours();
      mins = timeClient.getMinutes();
      secs = timeClient.getSeconds();
      days = timeClient.getDay();

      rtcNow = rtc.getTime();

      rtc.setTime(secs, mins, hrs, rtcNow.date, rtcNow.month, rtcNow.year); // установка даты и времени вручную
    }
  }
}
