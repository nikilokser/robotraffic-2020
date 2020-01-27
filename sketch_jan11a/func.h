#include <Wire.h>
#include <Octoliner.h>
#include <Servo.h>
#include <SharpIR.h>

Octoliner octoliner(42);
Octoliner octoliner1(45);
Servo servo;
SharpIR sharp(A6, 1080);

int w[] = { -1, -2, -3, -4, -5, -6, -7, -8};
int w1[] = {8, 7, 6, 5, 4, 3, 2, 1};

int motor[3] = {3, 24, 25};
int old = 0;
int encoder = 0;
int s = 0;
int deg = 90;
int default_speed = 80;

unsigned long timing;
bool left_on = 0;
bool right_on = 0;
bool f = 1;
bool st = 0;
int ts;
int ss;
int ir;
int octo;

#define stopp 50
#define left 52
#define right 51
#define enc 0


void encoder_plus() {
    encoder++;
}

float readline() {
    int sum = 0;
    int sumw = 0;
    // считываем значение с датчиков линии
    for (int i = 0; i < 8; i++) {
        // выводим значения в Serial-порт
        sumw += octoliner.analogRead(i) * w[i];
        sum += octoliner.analogRead(i);
    }
    for (int i = 0; i < 8; i++) {
        // выводим значения в Serial-порт
        sumw += octoliner1.analogRead(i) * w1[i];
        sum += octoliner1.analogRead(i);
    }
    float res = float(sumw) / sum;
    res = map(res * 100, -500, 500, -100, 100);
    res = constrain(res, -100, 100);
    return res;
}

float digital_sensors() {
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
  res = map(res, -8, 8, -100, 100);
  return res;
}

float pid(float p, float i, float d, bool digit) {
    float in;
    if (digit == 1) in = digital_sensors();
    else in = readline();
    float out = 0;
    float integral;
    float err = 0 + in;
    float change_in = old - in;
    integral += err * i;
    out += err * p + change_in * d + integral;
    old = in;
    out = map(out, -100, 100, 120, 60);
    out = constrain(out, 60, 120);
    return out;
}

//void lights(int s, int d) {
//  if (s < 100) {
//    digitalWrite(stopp, 1);
//  }
//  else {
//    digitalWrite(stopp, 0);
//    if (d > 105) {
//      digitalWrite(left, left_on);
//    }
//    else if (d < 75) {
//      digitalWrite(right, right_on);
//    }
//    else {
//      digitalWrite(right, 0);
//      digitalWrite(left, 0);
//    }
//  }
//}

void stopsig(int s) {
    if (s == 0 || (s < 30 && f == 1)) digitalWrite(stopp, 1);
    else digitalWrite(stopp, 0);
}

void delay_mil() {
    if (millis() - timing > 250) {
        left_on = !left_on;
        right_on = !right_on;
        timing = millis();
    }
}

void servo_pos(int degres) {
    degres = constrain(degres, 60, 120);
    servo.write(degres);
}

int IRread() {
    int in = -1;
    while (Serial1.available()) {
        in = Serial1.read();
    }
    return in;
}

void waitGreen() {
    int ir = IRread();
    while (ir != 2) {
        do {
            ir = IRread();
        } while (ir == -1);
        Serial.println(ir);
    }
}



void set() {
  pinMode(stopp, OUTPUT);
  pinMode(left, OUTPUT);
  pinMode(right, OUTPUT);

  Serial.begin(9600);
  Serial1.begin(115200);
  Wire.begin();
  
  octoliner.begin();
  Serial.println("octoliner ok");
  octoliner1.begin();
  Serial.println("octoliner2 ok");
  
  octoliner.setSensitivity(200);
  octoliner1.setSensitivity(200);
  
  octoliner.setBrightness(255);
  octoliner1.setBrightness(255);
  
  servo.attach(14);
  Serial.println("servo ok");
  
  attachInterrupt(enc, encoder_plus, RISING);
}

void go(int pwm, bool f) {
    stopsig(pwm);
    if (pwm == 0) {
        digitalWrite(motor[1], 0);
        digitalWrite(motor[2], 0);
    }
    else {
        analogWrite(motor[0], pwm);
        
        if (f == 0) {
            digitalWrite(motor[1], 0);
            digitalWrite(motor[2], 1);
        }
        else {
            digitalWrite(motor[1], 1);
            digitalWrite(motor[2], 0);
        }
    }
}

void jopa() {
    int dist = sharp.distance();
    int trace = map(default_speed, 50, 255, 30, 100);
    if (dist <= trace && st == 0) {
        digitalWrite(stopp, 1);
        if (default_speed < 100) {
          ss = 0;
          ts = 0;
        }
        else {
          ts = default_speed * 2;
          ss = 250;
        }
        go(ss, 0);
        delay(ts);
        f = 1;
        s = 0;
        st = 1;
    }
    else if (dist >= (trace+5)){
      s = default_speed;
      f = 1;
      st = 0;
    }
}
