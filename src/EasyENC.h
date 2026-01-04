#pragma once
#include <Arduino.h>

template<uint8_t DT, uint8_t CLK, uint8_t typeEnc>
struct EasyENC {
  EasyENC() {
    //  обьявляем пины как вход
    pinMode(DT, INPUT_PULLUP);
    pinMode(CLK, INPUT_PULLUP);
    e0 = digitalRead(CLK);
    e1 = digitalRead(DT);
  }
  
  //обработка энкодера
  int8_t epos;
  boolean p0, p1, e0, e1;
  int8_t direct;

  // обработчик энкодера
  int8_t pollEnc() {
    e0 = digitalRead(CLK);
    e1 = digitalRead(DT);
    if (p0 ^ p1 ^ e0 ^ e1) {
      (p1 ^ e0) ? ++epos : --epos;
      p0 = e0, p1 = e1;
      if (!epos) direct = 0;

      switch (typeEnc) {
        case 1:
          if (!(e0 & e1)) return 0;  // скип 01, 10, 00
          break;
        case 2:
          if (e0 | e1) return 0;  // скип 01, 10, 11
          break;
        case 3:
          if (e0 ^ e1) return 0;  // скип 10 01
          break;
      }
      int8_t state = epos > 0 ? -1 : 1;
      epos = 0;
      return state;
    }
    return 0;
  }

  // тикер, меняет значение переменой(вызывать в луп)
  void tick() {
    direct = pollEnc();
  }
};
