#include "tempSensorDriver\ds18B20-universal-driver.hpp"

// Global const defines

#define ISDEBUG true

#define OWPIN 5

#define TEMPERATUREOFFSET -1.64

// Global vars

String command;

OneWire oneWire = OneWire(OWPIN);

DsDriver ds;

void setup()
{
  Serial.begin(19200);
  Serial.println("BOOT");

  ds = DsDriver(TEMPERATUREOFFSET, oneWire, ISDEBUG);
  ds.scanSensors();

  Serial.println("BOOT OK");
}

void loop()
{
  if (Serial.available())
  {
    command = Serial.readStringUntil('\n');
    command.trim();
    if (command.equals("listAll"))
    {
      ds.listSensorsToSerial();
    }
    else if (command.equals("readAllC"))
    {
      ds.readSensortemperaturesInCelsius();
      ds.printTemperatures();
    }
    else if (command.equals("readIndex0"))
    {
      Serial.println(ds.readSensortemperatureInCelsiusByIndex(0));
    }
    else
    {
      Serial.println("bad command");
    }
    Serial.print("Executed command: ");
    Serial.println(command);
  }
}
