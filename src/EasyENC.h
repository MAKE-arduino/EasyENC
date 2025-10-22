#pragma once
#include <Arduino.h>

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
      _e0 = digitalRead(_CLK);
      _e1 = digitalRead(_DT);
      //переменную типа из публичной в приватную
      _typeEnc = typeEnc;
    }

    // тикер, меняет значение переменой(вызывать в луп)
    void tick() {
      direct = pollEnc();
    }
    // приватная зона

  private:
    // переменные
    int8_t _epos;
    uint8_t _DT, _CLK, _typeEnc;
    boolean _p0, _p1, _e0, _e1;
    // обработчик энкодера
    int8_t pollEnc() {
      _e0 = digitalRead(_CLK);
      _e1 = digitalRead(_DT);
      if (_p0 ^ _p1 ^ _e0 ^ _e1) {
        (_p1 ^ _e0) ? ++_epos : --_epos;
        _p0 = _e0, _p1 = _e1;
        if (!_epos) direct = 0;

        switch (_typeEnc) {
          case 1:
            if (!(_e0 & _e1)) return 0;  // skip 01, 10, 00
            break;
          case 2:
            if (_e0 | _e1) return 0;  // skip 01, 10, 11
            break;
          case 3:
            if (_e0 ^ _e1) return 0;  // skip 10 01
            break;
        }
        int8_t state = _epos > 0 ? -1 : 1;
        _epos = 0;
        return state;
      }
      return 0;
    }
};
