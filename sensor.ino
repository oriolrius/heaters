#include "Arduino.h"
#include "sensor.h"


int SensorReadTemp(void)
{ 
  Serial.print("Analog PIN:");  Serial.println(PIN_TEMP_SENSOR);

  int reading = analogRead(PIN_TEMP_SENSOR);  

  Serial.print("Reading:"); Serial.println(reading);

  float voltage = reading * 3.3;
  voltage /= 1024.0;
  
  Serial.print(voltage); Serial.println(" volts");
  
  float temperatureC = (voltage - 0.5 ) * 100;
  
  Serial.print(temperatureC); Serial.println(" degrees C");

  unsigned int tx_value = temperatureC * 100;
  Serial.print(tx_value); Serial.println(" volts");  
  Serial.println("---");  
  return tx_value;
}  

int setRelay(boolean value)
{
  Serial.print("Relay:"); Serial.println(value);
  Serial.println("---");    
  digitalWrite(PIN_HEATING, value);
}
