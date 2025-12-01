#include <Wire.h>
#include "DHT.h"
#include "Adafruit_SGP30.h"

#define DHTTYPE DHT20 // Grove DHT20 (I2C)
DHT dht(DHTTYPE);

Adafruit_SGP30 sgp;

// Convert T + RH -> absolute humidity (mg/m^3)
uint32_t getAbsoluteHumidity(float temperature, float humidity) {
    float absH = 216.7f * ((humidity / 100.0f) * 6.112f *
                 exp((17.62f * temperature) / (243.12f + temperature)) /
                 (273.15f + temperature));
    return (uint32_t)(absH * 1000.0f); // mg/m^3
}

void setup() {
  Serial.begin(115200);
  Wire.begin();

  Serial.println("Starting DHT20 + SGP30 combined sensor...");

  dht.begin();

  if (!sgp.begin()) {
    Serial.println("SGP30 not found. Check wiring.");
    while (1);
  }

  Serial.print("SGP30 serial: ");
  Serial.print(sgp.serialnumber[0], HEX);
  Serial.print(sgp.serialnumber[1], HEX);
  Serial.println(sgp.serialnumber[2], HEX);
}

void loop() {
  float vals[2];
  if (dht.readTempAndHumidity(vals)) {
    Serial.println("Failed to read from DHT20");
    delay(1000);
    return;
  }

  float humidity = vals[0];
  float temperature = vals[1];

  // Feed absolute humidity into SGP30 to improve accuracy
  uint32_t absHum = getAbsoluteHumidity(temperature, humidity);
  sgp.setHumidity(absHum);

  // Measure IAQ data
  if (!sgp.IAQmeasure() || !sgp.IAQmeasureRaw()) {
    Serial.println("SGP30 measurement failed");
    delay(1000);
    return;
  }

  // output
  Serial.print("temperature_c "); Serial.println(temperature, 2);
  Serial.print("humidity_percent "); Serial.println(humidity, 2);
  Serial.print("sgp30_tvoc_ppb "); Serial.println(sgp.TVOC);
  Serial.print("sgp30_eco2_ppm "); Serial.println(sgp.eCO2);
  Serial.print("sgp30_raw_h2 "); Serial.println(sgp.rawH2);
  Serial.print("sgp30_raw_ethanol "); Serial.println(sgp.rawEthanol);

  delay(1000); // interval
}

