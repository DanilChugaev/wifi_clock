#include "digit.h"

/** Класс вывода часов на дисплее */
class MegaClock
{
  public:
    MegaClock(CRGB *leds, uint8_t x, uint8_t y, int8_t time_shift, CRGB color);
    void update(int8_t hour, int8_t minute);

  private:
    uint8_t _width;
    uint8_t _height;
    uint8_t _minutePosition;
    uint8_t _nextNumberPosition;
    char _cstr[2];        // выделяем место под число в строке
    uint8_t _x = 0;
    uint8_t _y = 0;
    int8_t _time_shift;
    CRGB _color;
    void _createNumber(int8_t number, uint8_t x, uint8_t y);
    MegaDigit *_digit;
};

/**
 * Конструктор clock
 *
 * @param {uint8_t} x - положение пикселя по оси x
 * @param {uint8_t} y - положение пикселя по оси y
 * @param {int8_t} time_shift - смещение часового пояса
 * @param {CRGB} color - цвет пикселя
 */
MegaClock::MegaClock(CRGB *leds, uint8_t x, uint8_t y, int8_t time_shift, CRGB color) {
  _x = x;
  _y = y;
  _time_shift = time_shift;
  _color = color;
  
  _width = 3;
  _height = 5;
  _minutePosition = (_width * 2) + 3;
  _nextNumberPosition = _width + 1;

  // объявляем объект класса MegaDigit
  _digit = new MegaDigit(leds, _width, _height, _color);
}

/** Обновляет состояние часов */
void MegaClock::update(int8_t hour, int8_t minute) {
//  now.hour += _time_shift;

//  Serial.print(hour);
//  Serial.print("---");
//  Serial.println(minute);

  _createNumber(hour, _x, _y);
  _createNumber(minute, _x + _minutePosition, _y);
}

void MegaClock::_createNumber(int8_t number, uint8_t x, uint8_t y) {
  itoa(number, _cstr, DEC);  // переводим число в строку

  if (strlen(_cstr) == 2) {
//    _digit->create(_cstr[0], x, y);
//    _digit->create(_cstr[1], x + _nextNumberPosition, y);
//    _digit->create(1, x, y);
    _digit->create(2, x + _nextNumberPosition, y);
  } else {
    _digit->create(0, x, y);
    _digit->create(_cstr[0], x + _nextNumberPosition, y);
  }
}
