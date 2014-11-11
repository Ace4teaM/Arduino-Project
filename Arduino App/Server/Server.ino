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
Exemple de commande transmisible par paquet UDP (active la pin 9):  "cmd=on;pin=9;val=1;"

*/

#include <Arduino.h>
#include <inttypes.h>
// Librairie 'Serveur'
#include "Serveur.h"
#ifdef ETHERNET
#include <Dhcp.h>
#include <Dns.h>
#include <Ethernet.h>
#include <EthernetClient.h>
#include <EthernetServer.h>
#include <EthernetUdp.h>
#include <util.h>
#include "EthernetServeur.h"
#elif defined WIFI
#include <SPI.h>
#include <WiFi.h>
#include <WiFiClient.h>
#include <WiFiServer.h>
#include <WiFiUdp.h>
#include "WifiServeur.h"
#endif
#include "SwitchObjet.h"
#include "BuiltObjet.h"

// Librairie additionnelles
#include "LedStripObjet.h"

#ifdef ETHERNET
const byte _mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
#elif defined WIFI
const byte _mac[] = { 0x90, 0xA2, 0xDA, 0x0D, 0xB8, 0xE1 };
#endif
const byte _ip[] = { 192, 168, 1, 33 };
const char * serverId = "LedStrip";
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
        LedStripObjet strip;
        
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
	    this->InitialiseSerial();
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
              
            //execute les messages series
            if(this->LireMessageSerie(&message))
              this->ExecuterMessage(&message);
        }

        // Obtient la liste des objets
        int Objets(Objet** list){
            int i=0;
            
            // led switch
            for(int x=0; x<sizeof(led)/sizeof(SwitchObjet); x++)
              list[i++] = &led[x];
            
            // arduino mega objet
            list[i++] = &built;
            
            // ledstrip
            list[i++] = &strip;
            
            return i;
        }
        
	void InitialiseObjets(){
            Serial.println("Initialize objects...");
            
            this->led[0] = SwitchObjet("led_1",22,0);
            this->led[1] = SwitchObjet("led_2",26,0);
            this->led[2] = SwitchObjet("led_3",30,0);
            this->led[3] = SwitchObjet("led_4",34,0);
            this->built  = BuiltObjet("built");
            
            this->strip = LedStripObjet("strip",22,4,LEDSTRIP_MODE_DECALE);

            this->nObjets = Objets(this->pObjets);
	}

	void InitialiseSerial(){
		// Open serial communications and wait for port to open:
		Serial.begin(9600);
		while (!Serial) {
			; // wait for serial port to connect. Needed for Leonardo only
		}
	}
        // Obtient la liste des equipements
        int Equipements(Equipement** list){
          return 0;
        }
};

ServerApp app;

void setup() {
     app.Initialise();
}

void loop() {
    app.Periode();
    delay(100);
}

