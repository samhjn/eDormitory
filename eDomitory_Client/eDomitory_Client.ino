#include <SPI.h>
#include <Mirf.h>
#include <nRF24L01.h>
#include <MirfHardwareSpiDriver.h>

#include "settings.h"
#include "switchCtrl.h"
#include "sensorCtrl.h"
#include "command.h"

int role=0;
int id=0;
switchCtrl *switches[1];
sensorCtrl *sensors[1];

int refreshCount=0;

void doClientRefresh()
{
  
}

void setup() {
  int i;
  char addr[6];
  
  for (i=0;i<4;++i)
  {
    id*=2;
    if (analogRead(idPin[i])>512) id++;
  }
  
  for (i=0;i<3;++i)
  {
    pinMode(rolePin[i],INPUT_PULLUP);
  }

  for (i=0;i<3;++i)
  {
    role=role*2;
    role+=digitalRead(rolePin[i]);
  }

  if (role/4!=0)
  {
    switches[0]=new switchCtrl(role%4,switchPin[0]);
  }
  else
  {
    sensors[0]=new sensorCtrl(role,sensorPin[0]);
  }

  sprintf(addr,"cli%02d",id);
  
  Serial.begin(9600);

  Mirf.spi = &MirfHardwareSpi;
  Mirf.init();
  Mirf.setRADDR((byte *)addr);
  Mirf.setTADDR((byte *)"serv0");
  Mirf.payload = sizeof(command);
  Mirf.config();

  Serial.println("Beginning ... "); 
  Serial.print("ID:");
  Serial.println(id);
  Serial.print("Address:");
  Serial.println(addr);
  Serial.print("Role:");
  Serial.println(role);
}

void loop() {
   byte MirfRecieved[Mirf.payload];
   struct command commandRecieved;

   refreshCount+=1;
   refreshCount%=REFRESH_COUNT;
  
  if (Mirf.dataReady())
  {
    Serial.println("Got command");
    Mirf.getData(MirfRecieved);
    commandRecieved=(*(struct command *)MirfRecieved);
    //if ()
  }

  if (refreshCount==1)
  {
    doClientRefresh();
  }

}
