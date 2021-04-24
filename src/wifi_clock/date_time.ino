/*
 * Обновляет время из интернета с периодом NTP_SERVER_INTERVAL
 * Формат передачи в setTime - SEC, MIN, HOUR, DAY, MONTH, YEAR
 */
void updateDateTime() {
  if (internet_connected) { // и прошло NTP_SERVER_INTERVAL времени, с момента последнего обновления
    // DateTime now = getDateTimeFromInternet();
    // rtc.setTime(now.second, now.minute, now.hour, now.date, now.month, now.year); // установка даты и времени вручную
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
//DateTime getDateTimeFromInternet() {
//  
//}
