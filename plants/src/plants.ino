#include "PietteTech_DHT.h" 

#define DHTTYPE  AM2301       // Sensor type DHT11/21/22/AM2301/AM2302
#define DHTPIN   D3          // Digital pin for communications

PietteTech_DHT DHT(DHTPIN, DHTTYPE);

void setup() {
  Spark.publish("log", DHTLIB_VERSION);
  pinMode(A5, INPUT);
  DHT.begin();
}

void loop() {
  char topic[40];
  int light = analogRead(A0);
  int value = analogRead(A5);
  sprintf(topic, "moist-%d", A5);
  float moisturePerc = (100 - ((value / 4095.00) * 100 ));

  int result = DHT.acquireAndWait(1000); // wait up to 1 sec (default indefinitely)

  switch (result) {
  case DHTLIB_OK:
    break;
  case DHTLIB_ERROR_CHECKSUM:
    Spark.publish("log", "Error\n\r\tChecksum error");
    break;
  case DHTLIB_ERROR_ISR_TIMEOUT:
    Spark.publish("log", "Error\n\r\tISR time out error");
    break;
  case DHTLIB_ERROR_RESPONSE_TIMEOUT:
    Spark.publish("log", "Error\n\r\tResponse time out error");
    break;
  case DHTLIB_ERROR_DATA_TIMEOUT:
    Spark.publish("log", "Error\n\r\tData time out error");
    break;
  case DHTLIB_ERROR_ACQUIRING:
    Spark.publish("log", "Error\n\r\tAcquiring");
    break;
  case DHTLIB_ERROR_DELTA:
    Spark.publish("log", "Error\n\r\tDelta time to small");
    break;
  case DHTLIB_ERROR_NOTSTARTED:
    Spark.publish("log", "Error\n\r\tNot started");
    break;
  default:
    Spark.publish("log", "Unknown error");
    break;
  }
  char msg[40];
  sprintf(msg, "%s:%d, %s:%f, %s:%f, %s:%f", 
    "light", light, 
    topic, moisturePerc, 
    "humidity", DHT.getHumidity(), 
    "temp", DHT.getCelsius());

  Spark.publish("test", String(msg));
  delay(5 * 60000);
}
