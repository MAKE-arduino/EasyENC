#pragma once
#include <Arduino.h>

class EasyENC {
  public:
    EasyENC(uint8_t SW, uint8_t DT, uint8_t CLK)
      : _SW(SW), _DT(DT), _CLK(CLK) {}
    
    void init(uint8_t typeEnc) {
      pinMode(_SW, INPUT_PULLUP);
      pinMode(_DT, INPUT_PULLUP);
      pinMode(_CLK, INPUT_PULLUP);
      _typeEnc = typeEnc;
    }
    int tick() {
      _pA = digitalRead(_CLK);
      _pB = digitalRead(_DT);
      if (_lastState != pA) {
        switch (_typeEnc) {
          case 1: // EB_STEP4_LOW
            if (!(e0 & e1)) return 0;  // skip 01, 10, 00
            break;
          case 2: // EB_STEP4_HIGH
            if (e0 | e1) return 0;  // skip 01, 10, 11
            break;
          case 3: // EB_STEP2
            if (e0 ^ e1) return 0;  // skip 10 01
            break;
        }
        _lastState = _pA;
        return pB ^ pA
      }
      return 0;
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
    boolean _lastState;
    uint32_t _tmrSwRd;
};
