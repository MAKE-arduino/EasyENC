# EasyENC
Простая и не перегруженная библиотека.
## примеры
### вот пример:

```cpp
#include<EasyENC.h>
EasyENC enc(3, 2);
void setup() {
  enc.init(2);
  Serial.begin(115200);
}
int8_t counter;
void loop() {
  enc.tick(2); // сколько срабатываний за 1 щелчёк(шаг) выдаёт энкодер
  if (enc.direct == 1) Serial.println("right");
  if (enc.direct == -1) Serial.println("left");
}
```
## Примечание
Библиотека **не поддерживает кнопку(просто не указывайте в обьекте), ждите обновления**
