#pragma once
#include <Arduino.h>

class EasyENC {
  public:
    EasyENC(uint8_t SW, uint8_t DT, uint8_t CLK)
      : _SW(SW), _DT(DT), _CLK(CLK) {}
    
    void init() {
      pinMode(_SW, INPUT_PULLUP);
      pinMode(_DT, INPUT_PULLUP);
      pinMode(_CLK, INPUT_PULLUP);
      currentState = digitalRead(CLK);  
    }
    int tick() {
  _currentState = digitalRead(_CLK);
   if (_currentState != _initState  && _currentState == 1) {
    digitalRead(_DT) != currentState ? return 1 : return -1;
   }
  _initState = _currentState;
}
    boolean tickSW(boolean lvlBtn) {
      if (millis() - _tmrSwRd >= 30) {
        if (digitalRead(_SW) == lvlBtn) return true;
        else return false;
        _tmrSwRd = millis();
      }
    }
  private:
    uint8_t _SW, _DT, _CLK, _pA, _pB, _typeEnc;
    boolean _initState, _currentState;
    uint32_t _tmrSwRd;
};
