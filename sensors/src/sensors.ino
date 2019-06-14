#include "PietteTech_DHT.h" 

#define DHTTYPE  AM2301       // Sensor type DHT11/21/22/AM2301/AM2302
#define DHTPIN   D3          // Digital pin for communications

PietteTech_DHT DHT(DHTPIN, DHTTYPE);

void setup()
{
  Spark.publish("log", DHTLIB_VERSION);
  DHT.begin();
}

void loop()
{
  Spark.publish("log", "Read sensor:");

  int result = DHT.acquireAndWait(1000); // wait up to 1 sec (default indefinitely)

  switch (result) {
  case DHTLIB_OK:
    Spark.publish("log", "OK");
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
  Spark.publish("log", String(DHT.getHumidity()));
  Spark.publish("log", String(DHT.getCelsius()));

  delay(2500);
}
