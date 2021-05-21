/*
 * Обновляет время из интернета
 * Формат передачи в setTime - SEC, MIN, HOUR, DAY, MONTH, YEAR
 */
void updateDateTime() {
  if (WiFi.status() == WL_CONNECTED) {
    if (timeClient.update()) {
      hrs = timeClient.getHours();
      mins = timeClient.getMinutes();
      secs = timeClient.getSeconds();
      days = timeClient.getDay();

      DateTime now = rtc.getTime();

      rtc.setTime(secs, mins, hrs, now.date, now.month, now.year); // установка даты и времени вручную
    }
  }
}

/*
 * Получает время из модуля часов и учитывает смещение часового пояса
 * @param {int8_t} time_shift
 * @return {DateTime}
 */
DateTime getTimeFromRTC(int8_t time_shift = 0) {
  DateTime now = rtc.getTime();

  now.hour += time_shift;

  return now;
}

void printTime() {
  DateTime now = getTimeFromRTC();

  Serial.print(now.hour);
  Serial.print(":");
  Serial.print(now.minute);
  Serial.print(":");
  Serial.print(now.second);
  Serial.print(" ");
  Serial.print(now.day);
  Serial.print(" ");
  Serial.print(now.date);
  Serial.print("/");
  Serial.print(now.month);
  Serial.print("/");
  Serial.println(now.year);
}
