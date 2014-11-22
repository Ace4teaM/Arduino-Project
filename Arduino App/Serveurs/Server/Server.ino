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

#define ETHERNET

/*

Test d'interface de communication réseau (client/Serveur)

*/
//Adruino Lib
#include <Arduino.h>
#include <inttypes.h>
#include <SoftwareSerial.h>
#ifdef ETHERNET
#include <Dhcp.h>
#include <Dns.h>
#include <Ethernet.h>
#include <EthernetClient.h>
#include <EthernetServer.h>
#include <EthernetUdp.h>
#include <util.h>
#elif defined WIFI
#include <SPI.h>
#include <WiFi.h>
#include <WiFiClient.h>
#include <WiFiServer.h>
#include <WiFiUdp.h>
#endif

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
#ifdef ETHERNET
#include "EthernetServeur.h"
#elif defined WIFI
#include "WifiServeur.h"
#endif
#include "SwitchObjet.h"
#include "BuiltObjet.h"

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
#define COM

#ifdef ETHERNET
const byte _mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
#elif defined WIFI
const byte _mac[] = { 0x90, 0xA2, 0xDA, 0x0D, 0xB8, 0xE1 };
#endif
const byte _ip[] = { 192, 168, 1, 33 };
const char * serverId = "root";
const char * wifi_ssid = "AceTeaM";
const char * wifi_pwd = "emyleplusbeaudesbebes";

#ifdef ETHERNET
class ServerApp : public EthernetServeur{
  public:
	ServerApp() : EthernetServeur(serverId){}
#elif defined WIFI
class ServerApp : public WifiServeur{
  public:
	ServerApp() : WifiServeur(serverId){}
#endif
public:
        // objets
        SwitchObjet led[4];
        BuiltObjet built;
#ifdef COM
        ComObjet com;
#endif
        
        // liste des objets
        Objet* pObjets[EQUIPEMENT_MAX_OBJET];
        int nObjets;

	/*
	------------------------------------------
	Methodes
	------------------------------------------
	*/

	// initialise le programme
	void Initialise(){
	    this->InitialiseSerie();
            this->InitialiseObjets();
#ifdef ETHERNET
            this->InitialiseConnexion(_mac, _ip, false);
#elif defined WIFI
            this->InitialiseConnexion(_mac, _ip, wifi_ssid, wifi_pwd);
#endif
	    this->ConnexionReseau();
	}

        // Execute 
	void Periode(){
            MessageTexte message;
            
            //actualise les objets
            for(int i=0; i<nObjets; i++)
              this->pObjets[i]->Periode();
            
            //execute les messages reseau
            if(this->LireMessageReseau(&message))
              this->ExecuterMessage(&message);
              
            //execute les messages series (USB)
            if(this->LireMessageSerie(&message))
              this->ExecuterMessage(&message);
            
#ifdef COM
            // test
            /*if(strcmp(message.GetBuffer(),"test")==0){
              if(this->com.serialReady == false)
                Serial.println("Com not ready !");
              else if(this->com.serial != 0){
                Serial.println("Test send message");
                this->com.serial->println("test");
              }
            }*/

            //execute les messages series
            if(this->com.messageReady == true){
              this->ExecuterMessage(&this->com.message);
              this->com.messageReady = false; // permet la reception d'un nouveau message
            }
#endif
        }

        // Obtient la liste des objets
        int Objets(Objet** list){
            int i=0;
            
            // led switch
            for(int x=0; x<sizeof(led)/sizeof(SwitchObjet); x++)
              list[i++] = &led[x];
            
            // arduino mega objet
            list[i++] = &built;
            
            // communication
#ifdef COM
            list[i++] = &com;
#endif
            return i;
        }
        
	void InitialiseObjets(){
            Serial.println("Initialize objects...");
            
            this->led[0] = SwitchObjet("led_1",22,0);
            this->led[1] = SwitchObjet("led_2",26,0);
            this->led[2] = SwitchObjet("led_3",30,0);
            this->led[3] = SwitchObjet("led_4",34,0);
            this->built  = BuiltObjet("built");
            
#ifdef COM
            this->com = ComObjet("com","LedStrip",12,13); // RX, TX
#endif

            this->nObjets = Objets(this->pObjets);
	}

        // Obtient la liste des equipements
        int Equipements(Equipement** list){
          return 0;
        }
};

ServerApp app;

//SoftwareSerial mySerial(12, 13);// RX, TX

void setup() {
     app.Initialise();
     
    // set the data rate for the SoftwareSerial port
    //mySerial.begin(4800);
  Serial.print("FreeMemory=");
  Serial.print(freeMemory(),DEC);
  Serial.println(" bytes");
}

void loop() {
    app.Periode();
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

