/** Класс вывода часов на дисплее */
class MegaClock
{
  public:
    MegaClock(uint8_t x, uint8_t y, int8_t time_shift, CRGB color);
    void update(DateTime now);

  private:
    char _cstr[2];        // выделяем место под число в строке
    uint8_t _x = 0;
    uint8_t _y = 0;
    int8_t _time_shift = 0;
    CRGB _color = CRGB(0, 255, 0);
    void _createNumber(uint8_t number, uint8_t x, uint8_t y);
};

/**
 * Конструктор clock
 *
 * @param {uint8_t} x - положение пикселя по оси x
 * @param {uint8_t} y - положение пикселя по оси y
 * @param {int8_t} time_shift - смещение часового пояса
 * @param {CRGB} color - цвет пикселя
 */
MegaClock::MegaClock(uint8_t x, uint8_t y, int8_t time_shift = 0, CRGB color = CRGB(0, 255, 0)) {
  _x = x;
  _y = y;
  _time_shift = time_shift;
  _color = color;
}

/** Обновляет состояние часов */
void MegaClock::update(DateTime now) {
  now.hour += _time_shift;

  _createNumber(now.hour, _x, _y);
  _createNumber(now.minute, _x + 9, _y);
// 9 - это 2 ширины цифры + 1 - оступ между числами
}

void MegaClock::_createNumber(uint8_t number, uint8_t x, uint8_t y) {
  itoa(number, _cstr, DEC);  // переводим число в строку

  if (strlen(_cstr) == 2) {
    // _digit.create(_cstr[0], x, y);
    // _digit.create(_cstr[1], x + 4, y);
    // 4 - ширина 1 цифры
    Serial.println(_cstr);
  } else {
    // _digit.create(0, x, y);
    // _digit.create(_cstr[0], x + 4, y);
  }
}
