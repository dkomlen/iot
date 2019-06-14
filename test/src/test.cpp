#include "application.h"
#line 1 "/home/dkomlen/dkomlen/iot/test/src/test.ino"
void setup();
void publish_test();
void loop_blink_and_publish();
void loop_light_sensor();
void loop();
#line 1 "/home/dkomlen/dkomlen/iot/test/src/test.ino"
int val = 0;

void setup() {
  pinMode(D0, OUTPUT);
  pinMode(D7, OUTPUT);
  Particle.variable("analog", val);
}

void publish_test() {
  String data = "hello world";
  Particle.publish("test", data, PRIVATE);

}

void loop_blink_and_publish() {
  for (int i = 0; i < 6; ++i) {
    digitalWrite(D0, HIGH);
    delay(200);
    digitalWrite(D0, LOW);
    delay(10000);
  }

  digitalWrite(D7, HIGH);
  publish_test();
  digitalWrite(D7, LOW);
}

void loop_light_sensor() {
  val = analogRead(A5);
  if (val > 3500) {
    digitalWrite(D0, HIGH);
    delay(200);
    digitalWrite(D0, LOW);
  }
  
  delay(100);
}

void loop() {
  loop_light_sensor();
}