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
    _lastState = digitalRead(_CLK);
  }
int tick() {
  _state = digitalRead(_CLK);
  if (_state != _lastState) {
    if (digitalRead(_DT) != _state) {
      _lastState = _state;
      return 1;  // по часовой
    } else {
      _lastState = _state;
      return -1; // против часовой
    }
  }
  _lastState = _state;
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
  uint8_t _SW, _DT, _CLK;
  boolean _state, _lastState;
  uint32_t _tmrSwRd;
};
