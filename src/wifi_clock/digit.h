
class MegaDigit
{
  public:
    MegaDigit(CRGB *leds, uint8_t width, uint8_t height, CRGB color);
    void create(uint8_t n, uint8_t x, uint8_t y);

  private:
    CRGB *_leds;
    uint8_t _width;
    uint8_t _height;
    uint8_t _widthMinusOne;
    uint8_t _heightMinusOne;
    uint8_t _widthMinusOneHalf;
    uint8_t _heightMinusOneHalf;
    uint8_t _heightHalf;
    CRGB _color;
    void _createHorizontalLine(uint8_t x, uint8_t y);
    void _createVerticallLine(uint8_t x, uint8_t y, uint8_t customHeight);
    uint16_t _getPosition(uint8_t x, uint8_t y);
    void _createZero(uint8_t x, uint8_t y);
    void _createOne(uint8_t x, uint8_t y);
    void _createTwo(uint8_t x, uint8_t y);
    void _createThree(uint8_t x, uint8_t y);
    void _createFour(uint8_t x, uint8_t y);
    void _createFive(uint8_t x, uint8_t y);
    void _createSix(uint8_t x, uint8_t y);
    void _createSeven(uint8_t x, uint8_t y);
    void _createEight(uint8_t x, uint8_t y);
    void _createNine(uint8_t x, uint8_t y);
};

MegaDigit::MegaDigit(CRGB *leds, uint8_t width, uint8_t height, CRGB color) {
  _leds = leds;
  _width = width;
  _height = height;
  _color = color;

  _widthMinusOne = _width - 1;
  _heightMinusOne = _height - 1;
  _widthMinusOneHalf = _widthMinusOne / 2;
  _heightMinusOneHalf = _heightMinusOne / 2;
  _heightHalf = _heightMinusOneHalf + 1;
}

/**
 * Create digit from number
 *
 * @param {uint8_t} n - цифра
 * @param {uint8_t} x - положение пикселя по оси x
 * @param {uint8_t} y - положение пикселя по оси y
 *
 * @return {void}
 */
void MegaDigit::create(uint8_t n, uint8_t x, uint8_t y) {
  switch(n) {
    case 0:
      _createZero(x, y);
      break;
      
    case 1:
      _createOne(x, y);
      break;
      
    case 2:
      _createTwo(x, y);
      break;

    case 3:
      _createThree(x, y);
      break;

    case 4:
      _createFour(x, y);
      break;

    case 5:
      _createFive(x, y);
      break;

    case 6:
      _createSix(x, y);
      break;

    case 7:
      _createSeven(x, y);
      break;

    case 8:
      _createEight(x, y);
      break;

    case 9:
      _createNine(x, y);
      break;
      
    default:
      _createZero(x, y);
      break;
  }
}

/**
 * Create number `0`
 *
 * @param {uint8_tuint8_t} x - положение пикселя по оси x
 * @param {uint8_tuint8_t} y - положение пикселя по оси y
 *
 * @return {void}
 */
void MegaDigit::_createZero(uint8_t x, uint8_t y) {
  _createHorizontalLine(x, y + _heightMinusOne);
  _createVerticallLine(x + _widthMinusOne, y, _height);

  _createHorizontalLine(x, y);
  _createVerticallLine(x, y, _height);
}

/**
 * Create number `1`
 *
 * @param {uint8_tuint8_t} x - положение пикселя по оси x
 * @param {uint8_tuint8_t} y - положение пикселя по оси y
 *
 * @return {void}
 */
void MegaDigit::_createOne(uint8_t x, uint8_t y) {
  _createVerticallLine(x + _widthMinusOne, y, _height);
}

/**
 * Create number `2`
 *
 * @param {uint8_tuint8_t} x - положение пикселя по оси x
 * @param {uint8_tuint8_t} y - положение пикселя по оси y
 *
 * @return {void}
 */
void MegaDigit::_createTwo(uint8_t x, uint8_t y) {
  _createHorizontalLine(x, y + _heightMinusOne);

  _createVerticallLine(x + _widthMinusOne, y + _heightMinusOneHalf, _heightMinusOneHalf);

  _createHorizontalLine(x, y + _heightMinusOneHalf);

  _createVerticallLine(x, y, _heightMinusOneHalf);
  
  _createHorizontalLine(x, y);
}

/**
 * Create number `3`
 *
 * @param {uint8_tuint8_t} x - положение пикселя по оси x
 * @param {uint8_tuint8_t} y - положение пикселя по оси y
 *
 * @return {void}
 */
void MegaDigit::_createThree(uint8_t x, uint8_t y) {
  _createHorizontalLine(x, y + _heightMinusOne);

  _createHorizontalLine(x, y + _heightMinusOneHalf);
  
  _createHorizontalLine(x, y);

  _createVerticallLine(x + _widthMinusOne, y, _height);
}

/**
 * Create number `4`
 *
 * @param {uint8_tuint8_t} x - положение пикселя по оси x
 * @param {uint8_tuint8_t} y - положение пикселя по оси y
 *
 * @return {void}
 */
void MegaDigit::_createFour(uint8_t x, uint8_t y) {
  _createVerticallLine(x, y + _heightMinusOneHalf, _heightHalf);
   
  _createHorizontalLine(x, y + _heightMinusOneHalf);

  _createVerticallLine(x + _widthMinusOne, y, _height);
}

/**
 * Create number `5`
 *
 * @param {uint8_tuint8_t} x - положение пикселя по оси x
 * @param {uint8_tuint8_t} y - положение пикселя по оси y
 *
 * @return {void}
 */
void MegaDigit::_createFive(uint8_t x, uint8_t y) {
  _createHorizontalLine(x, y + _heightMinusOne);  // верхняя линия
  
  _createVerticallLine(x, y + _heightMinusOneHalf, _heightHalf);  // левая линия
   
  _createHorizontalLine(x, y + _heightMinusOneHalf);  // средняя линия

  _createVerticallLine(x + _widthMinusOne, y, _heightMinusOneHalf); // правая линия

  _createHorizontalLine(x, y);;  // нижняя линия
}

/**
 * Create number `6`
 *
 * @param {uint8_tuint8_t} x - положение пикселя по оси x
 * @param {uint8_tuint8_t} y - положение пикселя по оси y
 *
 * @return {void}
 */
void MegaDigit::_createSix(uint8_t x, uint8_t y) {
  _createHorizontalLine(x, y + _heightMinusOne);  // верхняя линия
  
  _createVerticallLine(x, y, _height);  // левая линия
   
  _createHorizontalLine(x, y + _heightMinusOneHalf);  // средняя линия

  _createVerticallLine(x + _widthMinusOne, y, _heightMinusOneHalf); // правая линия

  _createHorizontalLine(x, y);;  // нижняя линия
}

/**
 * Create number `7`
 *
 * @param {uint8_tuint8_t} x - положение пикселя по оси x
 * @param {uint8_tuint8_t} y - положение пикселя по оси y
 *
 * @return {void}
 */
void MegaDigit::_createSeven(uint8_t x, uint8_t y) {
  _createHorizontalLine(x, y + _heightMinusOne);  // верхняя линия

  _createVerticallLine(x + _widthMinusOne, y, _height); // правая линия
}

/**
 * Create number `8`
 *
 * @param {uint8_tuint8_t} x - положение пикселя по оси x
 * @param {uint8_tuint8_t} y - положение пикселя по оси y
 *
 * @return {void}
 */
void MegaDigit::_createEight(uint8_t x, uint8_t y) {
  _createHorizontalLine(x, y + _heightMinusOne);  // верхняя линия
  _createVerticallLine(x + _widthMinusOne, y, _height); // правая линия

  _createHorizontalLine(x, y + _heightMinusOneHalf);  // средняя линия

  _createHorizontalLine(x, y);  // нижняя линия
  _createVerticallLine(x, y, _height);  // левая линия
}

/**
 * Create number `9`
 *
 * @param {uint8_tuint8_t} x - положение пикселя по оси x
 * @param {uint8_tuint8_t} y - положение пикселя по оси y
 *
 * @return {void}
 */
void MegaDigit::_createNine(uint8_t x, uint8_t y) {
  _createHorizontalLine(x, y + _heightMinusOne);  // верхняя линия
  _createVerticallLine(x + _widthMinusOne, y, _height); // правая линия

  _createHorizontalLine(x, y + _heightMinusOneHalf);  // средняя линия

  _createHorizontalLine(x, y);  // нижняя линия
  _createVerticallLine(x, y + _heightMinusOneHalf, _heightMinusOneHalf);  // левая линия
}

/**
 * Create horizontal line
 *
 * @param {uint8_tuint8_t} x - положение пикселя по оси x
 * @param {uint8_tuint8_t} y - положение пикселя по оси y
 *
 * @return {void}
 */
void MegaDigit::_createHorizontalLine(uint8_t x, uint8_t y) {
  for (int i = 0; i < _width; i++) {
    _leds[_getPosition(x + i, y)] = _color;
  }
}

/**
 * Create vertical line
 *
 * @param {uint8_tuint8_t} x - положение пикселя по оси x
 * @param {uint8_tuint8_t} y - положение пикселя по оси y
 *
 * @return {void}
 */
void MegaDigit::_createVerticallLine(uint8_t x, uint8_t y, uint8_t customHeight) {
  for (int i = 0; i < customHeight; i++) {
    _leds[_getPosition(x, y + i)] = _color;
  }
}

/*
 * Возвращает местоположение светодиода по указанным координатам
 * Счет идет слева снизу - вправо вверх
 * 
 * @param {int8_t} x - позиция по оси `x`
 * @param {int8_t} y - позиция по оси `y`
 *
 * @return {uint16_t}
 */
uint16_t MegaDigit::_getPosition(uint8_t x, uint8_t y) {
  return x % 2 != 0 ? x * HEIGHT + y : x * HEIGHT + (HEIGHT - 1) - y;
}
