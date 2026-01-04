# EasyENC
Простая и не перегруженная библиотека.
## примеры
### вот пример:

```cpp
#include<EasyENC.h>
EasyENC<2, 3, 1> enc; // DT, CLK, тип энкодера, читай READme
void setup() {
  Serial.begin(115200);
}

void loop() {
  enc.tick();
  if (enc.direct == 1) Serial.println("left");
  else if (enc.direct == -1) Serial.println("right");
}
```
## Примечание
Библиотека **не поддерживает кнопку(просто не указывайте в обьекте), ждите обновления**
