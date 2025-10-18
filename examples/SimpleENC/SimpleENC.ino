#include<EasyENC.h>
EasyENC enc(3, 2); // DT - 3, CLK - 2
void setup() {
  enc.init(2);  // сколько срабатываний за 1 щелчёк(шаг) выдаёт энкодер
  Serial.begin(115200);
}
int8_t counter;
void loop() {
  enc.tick();
  if (enc.direct == 1) Serial.println("right");
  if (enc.direct == -1) Serial.println("left");
}
