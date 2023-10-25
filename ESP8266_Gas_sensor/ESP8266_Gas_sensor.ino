#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

char auth[] = "iEzOccbHiAx3dnYZxQtZX281xRWnozwy";
char ssid[] = "prateeksingh";
char pass[] = "kumar@12345";

BlynkTimer timer;
int pinValue = 0;

#define Buzzer D1
#define Green D2
#define Red D3
#define Sensor A0

void setup() {
  Serial.begin(9600);
  pinMode(Green, OUTPUT);
  pinMode(Red, OUTPUT);
  pinMode(Buzzer, OUTPUT);
  pinMode(Sensor, INPUT);
  Blynk.begin(auth, ssid, pass, "blynk.cloud", 80);
}

void notifiaction() {
  int sensor = analogRead(Sensor);
  Serial.println(sensor);
  sensor = map(sensor, 0, 1024, 0, 100);
  Blynk.virtualWrite(V2, sensor);
  if (sensor <= 50) {
    digitalWrite(Green, HIGH);
    digitalWrite(Red, LOW);
    digitalWrite(Buzzer, LOW);
    WidgetLED LED(V0);
    LED.on();
    WidgetLED LED1(V1);
    LED1.off();
  } else {
    Blynk.notify("Warning! Gas leak detected");
    digitalWrite(Green, LOW);
    digitalWrite(Red, HIGH);
    digitalWrite(Buzzer, HIGH);
    WidgetLED LED(V0);
    LED.off();
    WidgetLED LED1(V1);
    LED1.on();
  }
}

void loop() {
  notifiaction();
  Blynk.run();
  delay(200);
}