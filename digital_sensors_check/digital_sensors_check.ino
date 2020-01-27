#include <Octoliner.h>

Octoliner octoliner(42);
Octoliner octoliner1(45);

int w[] = { -1, -2, -3, -4, -5, -6, -7, -8};
int w1[] = {8, 7, 6, 5, 4, 3, 2, 1};

int octo;

void setup() {
  Serial.begin(9600);
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
  int sum = 0;
  int sumw = 0;
  for (int i = 0; i < 8; i++) {
    if (octoliner1.analogRead(i) > 600) octo = 1;
    else octo = 0;
    sumw += octo * w1[i];
    sum += octo;
  }
  for (int i = 0; i < 8; i++) {
    if (octoliner.analogRead(i) > 600) octo = 1;
    else octo = 0;
    sumw += octo * w[i];
    sum += octo;
  }
  if (sum == 0) sum = 1;
  int res = sumw / sum;
  Serial.println(res);
}
