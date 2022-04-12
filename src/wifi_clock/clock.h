#include "digit.h"
MicroDS3231 rtc;

/** Класс вывода часов на дисплее */
class MegaClock
{
  public:
    MegaClock(CRGB *leds, uint8_t x, uint8_t y, int8_t time_shift, CRGB color);
    void update();

  private:
    uint8_t _width;
    uint8_t _height;
    uint8_t _minutePosition;
    uint8_t _nextNumberPosition;
    String _str;  // выделяем место под число в строке
    uint8_t _x = 0;
    uint8_t _y = 0;
    int8_t _time_shift;
    CRGB _color;
    DateTime _nowDateTime;
    void _createNumber(int8_t number, uint8_t x, uint8_t y);
    void _getTimeFromRTC(int8_t time_shift);
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
  _width = 3;       // ширина цифры
  _height = 5;      // высота цифры
  _minutePosition = (_width * 2) + 3;   // позиция минут относительно часов
  _nextNumberPosition = _width + 1;     // позиция рядом стоящей цыфры

  // объявляем объект класса MegaDigit
  _digit = new MegaDigit(leds, _width, _height, _color);
}

/** Обновляет состояние часов */
void MegaClock::update() {
  _getTimeFromRTC(_time_shift);
//  Serial.print(_nowDateTime.hour);
//  Serial.print("---");
//  Serial.println(_nowDateTime.minute);

  _createNumber(_nowDateTime.hour, _x, _y);
  _createNumber(_nowDateTime.minute, _x + _minutePosition, _y);
}

void MegaClock::_createNumber(int8_t number, uint8_t x, uint8_t y) {
  _str = String(number);

  if (_str.length() == 2) {
    _digit->create(_str.substring(0, 1).toInt(), x, y);
    _digit->create(_str.substring(1, 2).toInt(), x + _nextNumberPosition, y);
  } else {
    _digit->create(0, x, y);
    _digit->create(_str.substring(0, 1).toInt(), x + _nextNumberPosition, y);
  }
}

/*
 * Получает время из модуля часов и учитывает смещение часового пояса
 * 
 * @global_class rtc
 * @global_class DateTime
 * 
 * @param {int8_t} time_shift - смещение часового пояса
 * 
 * @return {DateTime}
 */
void MegaClock::_getTimeFromRTC(int8_t time_shift = 0) {
  _nowDateTime = rtc.getTime();

  _nowDateTime.hour += time_shift;
}
