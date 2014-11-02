
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

#define WIFI

/*

Test d'interface de communication réseau (client/Serveur)
Exemple de commande transmisible par paquet UDP (active la pin 9):  "cmd=on;pin=9;val=1;"

*/

#include <SPI.h>
#include <WiFi.h>
#include <WiFiClient.h>
#include <WiFiServer.h>
#include <WiFiUdp.h>

#include <Dhcp.h>
#include <Dns.h>
#include <Ethernet.h>
#include <EthernetClient.h>
#include <EthernetServer.h>
#include <EthernetUdp.h>
#include <util.h>

#include <SPI.h>
#include "Serveur.h"
#include "SwitchObjet.h"
#include "BuiltObjet.h"
#include "LedStripObjet.h"

const byte mac[] = { 0x90, 0xA2, 0xDA, 0x0D, 0xB8, 0xE1 };
const char * serverId = "LedStrip";
const char * wifi_ssid = "AceTeaM";
const char * wifi_pwd = "emyleplusbeaudesbebes";
const IPAddress static_ip = (192,168,1,50);

#ifdef ETHERNET
class ServerApp : public EthernetServeur{
  public:
	ServerApp() : EthernetServeur(serverId, mac, &static_ip){}
#elif defined WIFI
class ServerApp : public WifiServeur{
  public:
	ServerApp() : WifiServeur(serverId, mac, &static_ip){}
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
            this->InitialiseConnexion(true);
#elif defined WIFI
            this->InitialiseConnexion(wifi_ssid, wifi_pwd);
#endif
	    this->ConnexionReseau();
	}

        // Execute 
	void Periode(){
            //actualise les objets
            for(int i=0; i<nObjets; i++)
              this->pObjets[i]->Periode();
            //execute les messages reseau
            MessageTexte message;
            if(this->LireMessageReseau(&message))
              this->LireMessage(&message);
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
        // Lit un message sur le port serie
	int LireMessageSerie(){
          return 0;
        }
        // Ecrit un message sur le port serie
	void EcrireMessageSerie(){
        }
        // Execute une commande
	void ExecuterCommande(){
        }
        // Execute une commande
	void ExecuterConfiguration(){
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

