#include "func.h"

void setup() {
  set();
}

void loop() {
  float p = 0.8;
  float i = 0;
  float d = 2;
  s = 80;
  if (encoder > 5) {
    p = 0.1;
//    d = 0.2;
    s = 200;
  }
  if (encoder > 30) {
    s = 0;
  }
//  if (encoder > 30) {
//    p = 0.2;
//    d = 0.1;
//    s = 0;
//  }
//  if (encoder > 35) {
//    p = 1.5;
//    d = 1.5;
//    s = 50;
//  }
//  if (encoder > 43) {
//    p = 0.8;
//    i = 0.4;
//  }
//  if (encoder > 75) {
//    s = 80;
//  }
//  if (encoder > 80) {
//    p = 10;
//    d = 50;
//  }
//  if (encoder > 110) {
//    s = 120;
//    p = 3;
//    d = 10;
//  }
//  if (encoder > 130) {
//    s = 90;
//  }
//  if (encoder > 135) {
//    p = 8;
//    d = 30;
//  }
//  if (encoder > 195) {
//    s = 120;
//    p = 3;
//    d = 10;
//  }
//  if (encoder > 200) {
//    s = 90;
//  }
//  if (encoder > 205) {
//    p = 8;
//    d = 30;
//  }
  deg = pid(p, i, d);
  go(s, f);
  servo_pos(deg);
//  lights(s, deg);
//  delay_mil();
//  ir = IRread();
//  if (ir < 7 && ir != -1 && ir != 0) {
//    Serial.println(ir);
//    if (ir == 2 || ir == 3) {
//      s = 50;
//    }
//    else {
//      s = 0;
//    }
//  }
//  go(s, 90);
  opa();
  Serial.println(encoder);
  delay(1);
}
