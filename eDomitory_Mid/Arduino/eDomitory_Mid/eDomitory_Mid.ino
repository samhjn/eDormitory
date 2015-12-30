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

#include "command.h"

void (*resetFunc)(void) = 0; //Cause error to reset the chip

struct command cmd;

long data[DATA_COUNT-1];
long action;
int recieverId=10;
char addr[6];

void setup() {
  //Function that only run once to init the chip

  Serial.begin(9600);  //Init serial communication

  Mirf.spi = &MirfHardwareSpi;
  Mirf.init();
  Mirf.setRADDR((byte *)"serv0");
  Mirf.payload = sizeof(command);
  Mirf.config();  //Init nRF24L01+ module

  //Serial.println("Waiting ... "); 
}

void loop() {
  byte MirfRecieved[Mirf.payload];
  struct command commandRecieved;
  
  if (Mirf.dataReady()) //Recieve package if there is any
  {
    Mirf.getData(MirfRecieved);
    commandRecieved=(*(struct command *)MirfRecieved); //Get package
    
    if(commandToVar(commandRecieved,0,&action,data))  //Transport package to Raspberry Pi
    {
      Serial.println(action);
      for (int i=0;i<DATA_COUNT-1;++i)
      {
        Serial.println(data[i]);
      }
    }
    else
    {
      Serial.println(action);
      Serial.println(data[0]);
    }
  }
  
  if (!Mirf.isSending())  //Send package if there is any
  {
    if (Serial)
    {
      action = Serial.parseInt();
      for (int i=0;i<DATA_COUNT-1;++i)
      {
        data[i] = Serial.parseInt();
      }//Get command from Raspberry Pi
      
      varToCommand(action,data,&cmd); //Make package
      
      sprintf(addr,"cli%02d",recieverId); 
      //Serial.println(addr);
      Mirf.setTADDR((byte *)addr);
      Mirf.send((byte *)&cmd);
      //Serial.println("Command sent.");
      //Send package
      
      resetFunc();//Reset is requred or next package won't be sent
    }
  }
}

