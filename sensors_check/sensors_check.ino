#include <Octoliner.h>

Octoliner octoliner(42);
Octoliner octoliner1(45);

void setup() {
  Serial.begin(115200);
  // начало работы с модулями I²C
  Wire.begin();
  // начало работы с датчиками линии
  octoliner.begin();
  Serial.println("octoliner ok");
  octoliner1.begin();
  Serial.println("octoliner2 ok");
  // выставляем чувствительность фотоприёмников в диапазоне от 0 до 255
  octoliner.setSensitivity(200);
  octoliner1.setSensitivity(200);
  // выставляем яркость свечения ИК-светодиодов в диапазоне от 0 до 255
  octoliner.setBrightness(255);
  octoliner1.setBrightness(255);
}

void loop() {
  for (int i = 0; i < 8; i++) {
    // выводим значения в Serial-порт
    Serial.print(octoliner1.analogRead(i));
    Serial.print("\t");
  }
  for (int i = 0; i < 8; i++) {
    // выводим значения в Serial-порт
    Serial.print(octoliner.analogRead(i));
    Serial.print("\t");
  }
  Serial.println();
}
