class EasyENC {
public:
  EasyENC(uint8_t DT, uint8_t CLK)
    : _DT(DT), _CLK(CLK) {}
  // переменные
  int8_t direct;
  // инициализация(обязательно)
  void init(uint8_t typeEnc) {
    //  обьявляем пины как вход
    pinMode(_DT, INPUT_PULLUP);
    pinMode(_CLK, INPUT_PULLUP);
    _lastState = digitalRead(_CLK);
    //переменную типа из публичной в приватную
    _typeEnc = typeEnc;
  }
  // тикер, меняет значение переменой(вызывать в луп)
  void tick() {
    _state = digitalRead(_CLK);
    if (_state != _lastState) {
      digitalRead(_DT) != _state ? direct1() : direct2();
    } else direct = 0;
    _lastState = _state;
  }
  // приватная зона
private:
  // переменные
  uint8_t _DT, _CLK, _counter1, _counter2, _typeEnc;
  boolean _state, _lastState;
  //обработчики 2х и более срабатываний
  void direct1() {
    if (++_counter1 > _typeEnc) _counter1 = 1;
    if (_counter1 == 2) direct = 1;
  }
  void direct2() {
    if (++_counter2 > _typeEnc) _counter2 = 1;
    if (_counter2 == 2) direct = -1;
  }
};
