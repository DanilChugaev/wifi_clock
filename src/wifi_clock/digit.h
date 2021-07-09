
class digit
{
  public:
    digit(uint32_t interval);

  private:
    uint32_t _timer = 0;
    uint32_t _interval = 0;
};

digit::digit(uint32_t interval) {
  _interval = interval;
}
