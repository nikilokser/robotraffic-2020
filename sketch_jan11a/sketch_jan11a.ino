#include "func.h"

void setup() {
  set();
  delay(1000);
}

void loop() {
  r.Kp = 1;
  r.Ki = 0;
  r.Kd = 5;
  s = 120;
  if (encoder > 4) { // первая прямая
    r.Kp = 0.2;
    r.Kd = 2;
    s = 220;
  }
  if (encoder > 15){
    s = 200; 
  }
  if (encoder > 48) {
    s = 0;
  }
  if (encoder > 57) { // первый поворот
    r.Kp = 1.5;
    r.Ki = 1.7;
    r.Kd = 9;
    s = 150;
  }
  if (encoder > 93) { // вторая прямая
    r.integral = 0;
    r.Kp = 0.2;
    r.Ki = 0;
    r.Kd = 2;
    s = 170;
  }
  if (encoder > 123) {
    s = 0;
  }
  if (encoder > 125) { // второй поворот
    r.Kp = 1.5;
    r.Ki = 1.7;
    r.Kd = 9;
    s = 120;
  }
  if (encoder > 180) { // финишная прямая
    s = 200;
    r.Kp = 0.2;
    r.Ki = 0;
    r.Kd = 2;
  }
  if (encoder > 225) {
    s = 0;
  }
  int j = jopa(s);
  go(j, f);
  servo_pos(gyver());
  delay_mil();
}
