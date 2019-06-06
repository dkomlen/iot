#include "application.h"
#line 1 "/home/dkomlen/dkomlen/iot/test/src/test.ino"
// setup() runs once, when the device is first turned on.
void setup();
void loop();
#line 2 "/home/dkomlen/dkomlen/iot/test/src/test.ino"
void setup() {
  // Put initialization like pinMode and begin functions here.
}

// loop() runs over and over again, as quickly as it can execute.
void loop() {
  // The core of your code will likely live here.
  String data = "hello world";
  // Trigger the integration
  Particle.publish("test", data, PRIVATE);
  // Wait 60 seconds
  delay(60000);
}