#include <EEPROM.h>
#include "product.h"
#include "panstamp.h"
#include "regtable.h"
#include "sensor.h"

DECLARE_COMMON_CALLBACKS()

DEFINE_COMMON_REGISTERS()

REGISTER regRoomTemp(RoomTemp, sizeof(RoomTemp), &updtRoomTemp, NULL);
REGISTER regHeating(Heating, sizeof(Heating), NULL, &setHeating);
REGISTER regSrvHeating(SrvHeating, sizeof(SrvHeating), &updtSrvHeating, NULL);
REGISTER regDesiredTemp(DesiredTemp, sizeof(DesiredTemp), NULL, &setDesiredTemp);
REGISTER regTolerance(Tolerance, sizeof(Tolerance), NULL, &setTolerance);
REGISTER regOutdoorTemp(OutdoorTemp, sizeof(OutdoorTemp), NULL, &setOutdoorTemp);
REGISTER regOutdoorHum(OutdoorHum, sizeof(OutdoorHum), NULL, &setOutdoorHum);
REGISTER regOutdoorWind(OutdoorWind, sizeof(OutdoorWind), NULL, &setOutdoorWind);
REGISTER regResyncInterval(ResyncInterval, sizeof(ResyncInterval), NULL, &setResyncInterval);
REGISTER regManual(Manual, sizeof(Manual), NULL, &setManual);

DECLARE_REGISTERS_START()
  &regRoomTemp,
  &regHeating,
  &regSrvHeating,
  &regDesiredTemp,
  &regTolerance,
  &regOutdoorTemp,
  &regOutdoorHum,
  &regOutdoorWind,
  &regResyncInterval,
  &regManual
DECLARE_REGISTERS_END()

DEFINE_COMMON_CALLBACKS()

const void updtRoomTemp(byte rId)
{ 
  room_temp = SensorReadTemp();
  
  RoomTemp[0] = (room_temp >> 8) & 0xFF;
  RoomTemp[1] = room_temp & 0xFF; 
}

const void setHeating(byte rId, byte *value)
{
  memcpy(regTable[rId]->value, value, sizeof(value));
  
  if ( value == 0x0 ) 
  {
      setRelay(LOW);
  } else {
      setRelay(HIGH);
  }  
  //digitalWrite(PIN_HEATING, *value);

}


const void updtSrvHeating(byte rId)
{
  memcpy(regTable[rId]->value, Heating, sizeof(Heating));
}

const void setDesiredTemp(byte rId, byte *value)
{
  memcpy(regTable[rId]->value, value, sizeof(value));
}

const void setTolerance(byte rId, byte *value)
{
  memcpy(regTable[rId]->value, value, sizeof(value));
}

const void setOutdoorTemp(byte rId, byte *value)
{
  memcpy(regTable[rId]->value, value, sizeof(value));
}

const void setOutdoorHum(byte rId, byte *value)
{
  memcpy(regTable[rId]->value, value, sizeof(value));
}

const void setOutdoorWind(byte rId, byte *value)
{
  memcpy(regTable[rId]->value, value, sizeof(value));
}

const void setResyncInterval(byte rId, byte *value)
{
  memcpy(regTable[rId]->value, value, sizeof(value));
}

const void setManual(byte rId, byte *value)
{
  memcpy(regTable[rId]->value, value, sizeof(value));
}



