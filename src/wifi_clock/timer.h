// взято отсюда https://github.com/AlexGyver/GyverLamp/https://github.com/AlexGyver/GyverLamp/

class timer
{
  public:
    timer(uint32_t interval);				// объявление таймера с указанием интервала
    void setInterval(uint32_t interval);	// установка интервала работы таймера
    boolean isReady();						// возвращает true, когда пришло время. Сбрасывается в false сам (AUTO) или вручную (MANUAL)
    void reset();							// ручной сброс таймера на установленный интервал

  private:
    uint32_t _timer = 0;
    uint32_t _interval = 0;
};

timer::timer(uint32_t interval) {
  _interval = interval;
  _timer = millis();
}

void timer::setInterval(uint32_t interval) {
  _interval = (interval == 0) ? 1 : interval;    // защита от ввода 0
}

boolean timer::isReady() {
  uint32_t thisMls = millis();

  if (thisMls - _timer >= _interval) {
    do {
      _timer += _interval;

      if (_timer < _interval) break;          // переполнение uint32_t
    } while (_timer < thisMls - _interval);  // защита от пропуска шага

    return true;
  } else {
    return false;
  }
}

void timer::reset() {
  _timer = millis();
}
