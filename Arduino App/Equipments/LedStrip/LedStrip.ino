/*
---------------------------------------------------------------------------------------------------------------------------------------
(C)2013 Thomas AUGUEY <contact@aceteam.org>
---------------------------------------------------------------------------------------------------------------------------------------
This file is part of Arduino Project (AceTeaM).

This code is free: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This code is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with WebFrameWork.  If not, see <http://www.gnu.org/licenses/>.
---------------------------------------------------------------------------------------------------------------------------------------
*/

//Adruino Lib
#include <Arduino.h>
#include <inttypes.h>
#include <SoftwareSerial.h>

// Base lib
#include <Commande.h>
#include <ComObjet.h>
#include <Configuration.h>
#include <CRC32.h>
#include <Equipement.h>
#include <Evenement.h>
#include <Message.h>
#include <Objet.h>
#include <Parametre.h>
#include <MemoryFree.h>

// local include
#define COM
#include "LedStripEquipement.h"

/*
----------------------------------------------------
CRC
----------------------------------------------------
*/
static PROGMEM prog_uint32_t crc_table[16] = {
    0x00000000, 0x1db71064, 0x3b6e20c8, 0x26d930ac,
    0x76dc4190, 0x6b6b51f4, 0x4db26158, 0x5005713c,
    0xedb88320, 0xf00f9344, 0xd6d6a3e8, 0xcb61b38c,
    0x9b64c2b0, 0x86d3d2d4, 0xa00ae278, 0xbdbdf21c
};

unsigned long crc_update(unsigned long crc, byte data)
{
    byte tbl_idx;
    tbl_idx = crc ^ (data >> (0 * 4));
    crc = pgm_read_dword_near(crc_table + (tbl_idx & 0x0f)) ^ (crc >> 4);
    tbl_idx = crc ^ (data >> (1 * 4));
    crc = pgm_read_dword_near(crc_table + (tbl_idx & 0x0f)) ^ (crc >> 4);
    return crc;
}

unsigned long crc32(const char *s)
{
  unsigned long crc = ~0L;
  while (*s)
    crc = crc_update(crc, *s++);
  crc = ~crc;
  return crc;
}

unsigned long crc32l(const char *s, int length)
{
  unsigned long crc = ~0L;
  while (length--)
    crc = crc_update(crc, *s++);
  crc = ~crc;
  return crc;
}

/*
----------------------------------------------------
App
----------------------------------------------------
*/
LedStripEquipement equip;

void setup() {
     equip.Initialise();
    // set the data rate for the SoftwareSerial port
    //mySerial.begin(4800);
  Serial.print("FreeMemory=");
  Serial.print(freeMemory(),DEC);
  Serial.println(" bytes");
}

void loop() {
     equip.Periode();
    
    /*
    int packetSize = 0;
    char serialBuffer[128];
    mySerial.listen();
    if (mySerial.available()){
      Serial.print("Available data:");
      packetSize = mySerial.readBytesUntil('\n', serialBuffer, 127);
      Serial.println(packetSize,DEC);
      if(packetSize){
        serialBuffer[packetSize]=0;
        Serial.println(serialBuffer);
      }
    }
    
      mySerial.println("Hello");*/
    delay(100);
}

