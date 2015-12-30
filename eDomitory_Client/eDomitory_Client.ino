/*
    eDomitory
    Copyright (C) 2015  Samhjn

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License along
    with this program; if not, write to the Free Software Foundation, Inc.,
    51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */
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

void doClientRefresh() //Call mid system to refresh
{
  struct command cmd;
  long data[4]={0};

  data[0]=id;
  data[1]=role;
  data[3]=switches[0]->getState();
  varToCommand(1,data,&cmd);
  Mirf.send((byte*)&cmd);
}

int doSensorUpload()
{
  //TODO
}

void doAction(long action,long data) //Take action
{
  switch(action)
  {
    case 3: if (role/4!=0)
            {
              switches[0]->switchAction();
              Serial.println("Switch moved");
            }else
            {
              Serial.println("Invalid Action");
            }
            break;
    case 5: if (role/4!=0)
            {
              doSensorUpload();
              Serial.println("Data uploaded");
            }
            else
            {
              Serial.println("Invalid Action");
            }
            break;
    default: Serial.println("Invalid Action");
            break;
  }
}

void setup() //Function run once to init the system 
{
  int i;
  char addr[6];
  
  for (i=0;i<4;++i)
  {
    id*=2;
    if (analogRead(idPin[i])>512) id++;
  }//Read the device id 
  
  for (i=0;i<3;++i)
  {
    pinMode(rolePin[i],INPUT_PULLUP);
  }//Prepare to read the device role

  for (i=0;i<3;++i)
  {
    role=role*2;
    role+=digitalRead(rolePin[i]);
  }//Read the device role

  if (role/4!=0)
  {
    switches[0]=new switchCtrl(role%4,switchPin[0]);
  }
  else
  {
    sensors[0]=new sensorCtrl(role,sensorPin[0]);
  }//Create control class

  sprintf(addr,"cli%02d",id);
  Mirf.spi = &MirfHardwareSpi;
  Mirf.init();
  Mirf.setRADDR((byte *)addr);
  Mirf.setTADDR((byte *)"serv0");
  Mirf.payload = sizeof(command);
  Mirf.config();
  //Init nRF24L01+ module

  Serial.begin(9600);
  Serial.println("Beginning ... "); 
  Serial.print("ID:");
  Serial.println(id);
  Serial.print("Address:");
  Serial.println(addr);
  Serial.print("Role:");
  Serial.println(role);
  //Init serial and output debug information
}

void loop() {
   byte MirfRecieved[Mirf.payload];
   struct command commandRecieved;

   long action;
   long data;

   refreshCount+=1;
   refreshCount%=REFRESH_COUNT;  
  
  if (Mirf.dataReady()) //Recieve command and take action
  {
    Serial.println("Got command");
    Mirf.getData(MirfRecieved);
    commandRecieved=(*(struct command *)MirfRecieved);
    commandToVar(commandRecieved,1,&action,&data);
    doAction(action,data);
    doClientRefresh();
    refreshCount=2;
  }

  if (refreshCount==1) //Refresh or register client information in a period of time 
  {
    doClientRefresh();
  }

}
