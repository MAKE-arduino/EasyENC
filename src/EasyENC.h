class EasyENC {
public:
  EasyENC(uint8_t SW, uint8_t DT, uint8_t CLK)
    : _SW(SW), _DT(DT), _CLK(CLK) {}
  // переменные
  int8_t direct;
  // инициализация(обязательно)
  void init() {
    //  обьявляем пины как вход
    pinMode(_SW, INPUT_PULLUP);
    pinMode(_DT, INPUT_PULLUP);
    pinMode(_CLK, INPUT_PULLUP);
    _lastState = digitalRead(_CLK);
  }
  // тикер, меняет значение переменой(вызывать в луп)
  void tick() {
    _state = digitalRead(_CLK);
    if (_state != _lastState) {
      digitalRead(_DT) != _state ? direct1() : direct2();
    } else direct = 0;
    _lastState = _state;
  }

  // тикр кнопки, вовзращает True при нажатой кнопке. В функцию указать уровень кнопки при нажатии
  boolean tickSW(boolean lvlBtn) {
    if (millis() - _tmrSwRd >= 30) {
      if (digitalRead(_SW) == lvlBtn) return true;
      else return false;
      _tmrSwRd = millis();
    }
  }

private:
  uint8_t _SW, _DT, _CLK, _counter1, _counter2;
  boolean _state, _lastState;
  uint32_t _tmrSwRd, _tmrZeroDrct;
  boolean numBtn;

  void direct1(){  
    if(++_counter1 > 2)_counter1 = 1;
    if(_counter1 == 2)direct = 1;
  }
  void direct2(){
    if(++_counter2 > 2)_counter2 = 1; 
    if(_counter2 == 2)direct = -1;
  }
};
