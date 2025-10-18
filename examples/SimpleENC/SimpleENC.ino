#include<EasyENC.h>
EasyENC enc(2, 3, 4) // 2 - sw 3 - dt clk - 4
void setup() {
  enc.init();
  Serial.begin(115200);
}

void loop() {
  enc.tick();
  if(enc.direct == -1)Serial.printlln("Right"); // в право
  if(enc.direct == 1)Serial.printlln("Left"); // в лево
  if(enc.tickSW(false) == -1)Serial.printlln("Click"); // клик, в скобках указываем уровень кнопки при нажатии
}
