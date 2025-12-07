#include <DHT.h>
#include <Servo.h>

#define DHTPIN 2
#define DHTTYPE DHT22

DHT dht(DHTPIN, DHTTYPE);

const int LDR_PIN = A0;
const int GAS_PIN = A1;
const int PIR_PIN = 3;
const int OVERRIDE_PIN = 11;

const int RELAY_LIGHT = 4;
const int RELAY_FAN   = 5;
const int RELAY_EXH   = 6;
const int RELAY_ALARM = 7;

const int BUZZER_PIN = 8;
const int FAN_SERVO_PIN = 9;
const int EXH_SERVO_PIN = 10;

Servo fanServo;
Servo exhServo;

int ldrThreshold = 500;
float tempThreshold = 28.0;
int gasThreshold = 450;

int fanPos = 90, fanDir = 1;
unsigned long fanLastMove = 0;

int exhPos = 90, exhDir = 1;
unsigned long exhLastMove = 0;

void setup() {
  Serial.begin(9600);
  dht.begin();

  pinMode(PIR_PIN, INPUT);
  pinMode(OVERRIDE_PIN, INPUT_PULLUP);

  pinMode(RELAY_LIGHT, OUTPUT);
  pinMode(RELAY_FAN, OUTPUT);
  pinMode(RELAY_EXH, OUTPUT);
  pinMode(RELAY_ALARM, OUTPUT);

  pinMode(BUZZER_PIN, OUTPUT);

  // ACTIVE-HIGH relays: OFF = LOW
  digitalWrite(RELAY_LIGHT, LOW);
  digitalWrite(RELAY_FAN, LOW);
  digitalWrite(RELAY_EXH, LOW);
  digitalWrite(RELAY_ALARM, LOW);
  digitalWrite(BUZZER_PIN, LOW);

  fanServo.attach(FAN_SERVO_PIN);
  exhServo.attach(EXH_SERVO_PIN);

  fanServo.write(90);
  exhServo.write(90);

  Serial.println("System started");
}

void loop() {

  if (digitalRead(OVERRIDE_PIN) == LOW) {
    // Manual override: everything OFF
    digitalWrite(RELAY_LIGHT, LOW);
    digitalWrite(RELAY_FAN, LOW);
    digitalWrite(RELAY_EXH, LOW);
    digitalWrite(RELAY_ALARM, LOW);
    digitalWrite(BUZZER_PIN, LOW);

    fanServo.write(90);
    exhServo.write(90);

    Serial.println("MANUAL OVERRIDE");
    delay(250);
    return;
  }

  Serial.println("AUTO MODE");

  int ldrVal = analogRead(LDR_PIN);
  int gasVal = analogRead(GAS_PIN);
  int pirVal = digitalRead(PIR_PIN);
  float temperature = dht.readTemperature();

  if (isnan(temperature)) temperature = 0;

  Serial.print("LDR:"); Serial.print(ldrVal);
  Serial.print(" PIR:"); Serial.print(pirVal);
  Serial.print(" Temp:"); Serial.print(temperature);
  Serial.print(" Gas:"); Serial.println(gasVal);

  if (ldrVal > ldrThreshold && pirVal == HIGH) {
    digitalWrite(RELAY_LIGHT, HIGH); // ON
  } else {
    digitalWrite(RELAY_LIGHT, LOW);  // OFF
  }

  if (temperature >= tempThreshold) {
    digitalWrite(RELAY_FAN, HIGH);
    updateServoOscillation(&fanServo, &fanPos, &fanDir, &fanLastMove, 20);
  } else {
    digitalWrite(RELAY_FAN, LOW);
    fanServo.write(90);
    fanPos = 90;
    fanDir = 1;
    fanLastMove = 0;
  }

  if (gasVal > gasThreshold) {
    digitalWrite(RELAY_EXH, HIGH);     // ON
    digitalWrite(RELAY_ALARM, HIGH);   // ON
    digitalWrite(BUZZER_PIN, HIGH);    // ON

    updateServoOscillation(&exhServo, &exhPos, &exhDir, &exhLastMove, 20);
  } else {
    digitalWrite(RELAY_EXH, LOW);       // OFF
    digitalWrite(RELAY_ALARM, LOW);     // OFF
    digitalWrite(BUZZER_PIN, LOW);      // OFF

    exhServo.write(90);
    exhPos = 90;
    exhDir = 1;
    exhLastMove = 0;
  }

  delay(200);
}

void updateServoOscillation(Servo *s, int *pos, int *dir, unsigned long *lastTime, unsigned long interval) {
  unsigned long now = millis();
  if (*lastTime == 0) *lastTime = now;

  if (now - *lastTime >= interval) {
    *lastTime = now;
    int step = 2;
    *pos += (*dir) * step;

    if (*pos <= 60) { *pos = 60; *dir = 1; }
    if (*pos >= 120) { *pos = 120; *dir = -1; }

    s->write(*pos);
  }
}
