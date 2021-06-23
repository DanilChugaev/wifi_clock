/*
 * Получает значение с датчика освещенности
 * 
 * @return {unsigned int}
 */
unsigned int getBrightness() {
  return analogRead(A0);
}
