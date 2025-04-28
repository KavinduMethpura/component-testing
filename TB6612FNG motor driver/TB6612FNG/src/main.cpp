#include <Arduino.h>

#define AIN1  25
#define AIN2  26
#define PWMA  27
#define BIN1  32
#define BIN2  33
#define PWMB  14
#define STBY  12

#define ENCODER1_A 34
#define ENCODER1_B 35
#define ENCODER2_A 36
#define ENCODER2_B 39

volatile long encoder1Count = 0;
volatile long encoder2Count = 0;

void IRAM_ATTR encoder1A_ISR() {
  if (digitalRead(ENCODER1_A) == digitalRead(ENCODER1_B)) encoder1Count++;
  else encoder1Count--;
}

void IRAM_ATTR encoder2A_ISR() {
  if (digitalRead(ENCODER2_A) == digitalRead(ENCODER2_B)) encoder2Count++;
  else encoder2Count--;
}

void setup() {
  Serial.begin(115200);

  pinMode(AIN1, OUTPUT);
  pinMode(AIN2, OUTPUT);
  pinMode(PWMA, OUTPUT);
  pinMode(BIN1, OUTPUT);
  pinMode(BIN2, OUTPUT);
  pinMode(PWMB, OUTPUT);
  pinMode(STBY, OUTPUT);

  digitalWrite(STBY, HIGH); // Enable TB6612FNG

  pinMode(ENCODER1_A, INPUT_PULLUP);
  pinMode(ENCODER1_B, INPUT_PULLUP);
  pinMode(ENCODER2_A, INPUT_PULLUP);
  pinMode(ENCODER2_B, INPUT_PULLUP);

  attachInterrupt(digitalPinToInterrupt(ENCODER1_A), encoder1A_ISR, CHANGE);
  attachInterrupt(digitalPinToInterrupt(ENCODER2_A), encoder2A_ISR, CHANGE);
}

void loop() {
  // Example motor control
  digitalWrite(AIN1, HIGH);
  digitalWrite(AIN2, LOW);
  analogWrite(PWMA, 128); // 0-255 PWM speed

  digitalWrite(BIN1, HIGH);
  digitalWrite(BIN2, LOW);
  analogWrite(PWMB, 128);

  Serial.printf("Motor1 Encoder: %ld, Motor2 Encoder: %ld\n", encoder1Count, encoder2Count);
  delay(100);
}
