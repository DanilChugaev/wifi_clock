/*
 * Возвращает местоположение светодиода по указанным координатам
 * Нечетные полосы (начиная от 0 светодиода) идут вниз
 * Четные идут вверх
 * 
 * @param {int8_t} x - позиция по оси `x`
 * @param {int8_t} y - позиция по оси `y`
 *
 * @return {uint16_t}
 */
uint16_t getPosition(int8_t x, int8_t y) {
  return x % 2 != 0 ? x * HEIGHT + y : x * HEIGHT + (HEIGHT - 1) - y;
}
