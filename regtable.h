#ifndef _REGTABLE_H
#define _REGTABLE_H

#include "Arduino.h"
#include "register.h"
#include "commonregs.h"

DEFINE_REGINDEX_START()
  REGI_ROOM_TEMP,
  REGI_HEATING,
  REGI_SRV_HEATING,
  REGI_DESIRED_TEMP,
  REGI_TOLERANCE,
  REGI_OUTDOOR_TEMP,
  REGI_OUTDOOR_HUM,
  REGI_OUTDOOR_WIND,
  REGI_RESYNC_INTERVAL,
  REGI_MANUAL,
DEFINE_REGINDEX_END()

byte RoomTemp[2];
byte Heating[1];
byte SrvHeating[1];
byte DesiredTemp[2];
byte Tolerance[1];
byte OutdoorTemp[2];
byte OutdoorHum[1];
byte OutdoorWind[1];
byte ResyncInterval[1];
byte Manual[1];

const void updtRoomTemp(byte rId);
const void setHeating(byte rId, byte *value);
const void updtSrvHeating(byte rId);
const void setDesiredTemp(byte rId, byte *value);
const void setTolerance(byte rId, byte *value);
const void setOutdoorTemp(byte rId, byte *value);
const void setOutdoorHum(byte rId, byte *value);
const void setOutdoorWind(byte rId, byte *value);
const void setResyncInterval(byte rId, byte *value);
const void setManual(byte rId, byte *value);

#endif

