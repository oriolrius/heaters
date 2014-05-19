#include "regtable.h"
#include "panstamp.h"
#include "product.h"
#include "sensor.h"
#include <commonregs.h>

#define LEDPIN  4

int room_temp = 0; // actual room temperature



int desired_temp = 2300; // 23 degrees


int tolerance = 200; // 2 degrees


int periodicity_resync_interval = 60;




int counter_room_temp = 0,
    counter_resync_interval = 0;
int periodicity_room_temp = 15;

void setup()
{
Heating[0] = 0x1; // heater off by default
DesiredTemp[0] = (desired_temp >> 8) & 0xFF;
DesiredTemp[1] = desired_temp & 0xFF;
Tolerance[0] = tolerance & 0xFF;
ResyncInterval[0] = periodicity_resync_interval & 0xFF;
Manual[0] = 0x1; // automatic by default

  int i;
  Serial.begin(38400);
  pinMode(LEDPIN, OUTPUT);
  digitalWrite(LEDPIN, LOW);
  
  panstamp.init();
  panstamp.cc1101.setDevAddress(NETWORK_ADDRESS, true);
  panstamp.cc1101.setChannel(NETWORK_CHANNEL);

  getRegister(REGI_PRODUCTCODE)->getData();

  panstamp.enterSystemState(SYSTATE_SYNC);

  // blinking leds
  for(i=0 ; i<6 ; i++)
  {
    digitalWrite(LEDPIN, HIGH);
    delay(100);
    digitalWrite(LEDPIN, LOW);
    delay(400);
  }

  room_temp = SensorReadTemp(); // getting room temperature for first time
}


void loop()
{ 
  // send produc code every minute
  getRegister(REGI_PRODUCTCODE)->getData();

  // send heater status
  getRegister(REGI_HEATING)->getData();  

  // send room temperature every 15 minutes
  counter_room_temp++;
  if ( counter_room_temp > periodicity_room_temp ) {
    getRegister(REGI_ROOM_TEMP)->getData();
    
    counter_room_temp = 0;
  }

  // resync every 60 minutes
  counter_resync_interval++;
  if ( counter_resync_interval > periodicity_resync_interval ) {
    panstamp.enterSystemState(SYSTATE_RXOFF);
    delay(1000);
    panstamp.enterSystemState(SYSTATE_SYNC);
    
    counter_resync_interval = 0;
  }
  
  
  // manual mode control
  if (Manual[0] == 0x1)
  {
    if ( Heating[0] == 0x00 )
    {
      setRelay(LOW);
    } else {
      setRelay(HIGH);
    }
  } else {
    if ( room_temp < desired_temp - tolerance ) 
    {
      setRelay(HIGH);        
    } else {
      if ( room_temp > desired_temp + tolerance ) 
      {
        setRelay(LOW);
      }
    }
  }
  
  room_temp = SensorReadTemp();
  delay(60000);
}

