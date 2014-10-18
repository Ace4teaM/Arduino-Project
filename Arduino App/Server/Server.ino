
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
#ifdef WIFI
#include <WiFi.h>
#include <WiFiClient.h>
#include <WiFiServer.h>
#include <WiFiUdp.h>
#else
#include <Ethernet.h>
#include <EthernetUdp.h>
#endif
#include "Message.h"
#include "Commande.h"
#include "Configuration.h"

// interface ethernet
#define INPUT_PORT 8888
#define OUTPUT_PORT 12345
#define USE_DHCP 1
#define UDP_TX_PACKET_MAX_SIZE 200

class ServerApp{
private:
	/*
	------------------------------------------
	Données
	------------------------------------------
	*/
        MessageTexte message; // message en cours
        Commande commande; // commande en cours
        Configuration configuration; // configuration en cours

public:
	/*
	------------------------------------------
	Methodes
	------------------------------------------
	*/

	// initialise le programme
	void Initialise(){
		this->InitialiseSerial();
#ifdef WIFI
		this->InitialiseWifi();
#endif
#ifdef ETHERNET
		this->InitialiseEthernet();
#endif
	}

	// Réceptionner un message texte sur le réseau
	int LireMessageTexte(){
		// if there's data available, read a packet
		int packetSize = Udp.parsePacket();
		if (packetSize)
		{
			// message
			Serial.print("Received packet of size ");
			Serial.println(packetSize);
			Serial.print("From ");
			IPAddress remote = Udp.remoteIP();
			for (int i = 0; i < 4; i++)
			{
				Serial.print(remote[i], DEC);
				if (i < 3)
				{
					Serial.print(".");
				}
			}
			Serial.print(", port ");
			Serial.println(Udp.remotePort());

			// vérifie la limite du tempon
			if (packetSize >= UDP_TX_PACKET_MAX_SIZE){
				Serial.println("Too big UDP packet");
				return 0;
			}

			// read the packet into packetBufffer
			Udp.read(this->packetBuffer, UDP_TX_PACKET_MAX_SIZE);
			this->packetBuffer[packetSize] = 0;

                        // initialise le message actuel
                        this->message = MessageTexte(this->packetBuffer, packetSize);
                        if(this->message.Verifier()){
                          char* ofs = this->message.GetBuffer();
                          int type = -1;
			  Serial.println("message valide");
                          ofs=this->message.LireSignature(ofs);
                          ofs=this->message.LireType(ofs,&type);
                          
                          switch(type){
                            case MessageTypeCommande:
			      Serial.print("read command\n");
                              this->commande.LireParam(&this->message, ofs);
			      Serial.print(this->commande.CodeCmd);
			      Serial.print(this->commande.EquipId);
                              break;
                            case MessageTypeConfiguration:
			      Serial.print("read config\n");
                              this->configuration.LireParam(&this->message, ofs);
                              break;
                            default:
			      Serial.print("uknown message type\n");
                              return 0;
                          }
                        }
                        else{
			  Serial.println("message invalide");
                          this->message = MessageTexte();
                        }
                        return 1;
		}
                return 0;
	}

	// Envoyer un message texte sur le réseau
	void EcrireMessageTexte(){
		// send a reply, to the IP address and port that sent us the packet we received
		Udp.beginPacket(Udp.remoteIP(), OUTPUT_PORT);
		Udp.write(replyBuffer);
		Udp.endPacket();
	}

	// Parser un message texte 
	void ParserMessageTexte(){
	}

	// Exécuter une commande
	void ExecuterCommande(){
	}

	// Transmettre une commande
	void TransmettreCommande(){
	}

	// Exécuter une configuration
	void ExecuterConfiguration(){
	}

	/*
	------------------------------------------
	Serial
	------------------------------------------
	*/
	void InitialiseSerial(){
		// Open serial communications and wait for port to open:
		Serial.begin(9600);
		while (!Serial) {
			; // wait for serial port to connect. Needed for Leonardo only
		}
	}

	/*
	------------------------------------------
	Ethernet Shield
	------------------------------------------
	*/
#ifdef ETHERNET
	void InitialiseEthernet(){
		if (this.use_dhcp){
			if (Ethernet.begin(mac) == 0) {
				Serial.println("Failed to configure Ethernet using DHCP");
				// no point in carrying on, so do nothing forevermore:
				for (;;)
					;
			}
			// print local IP address:
			Serial.print("My IP address: ");
			Serial.println(Ethernet.localIP());
		}
		else{
			Ethernet.begin(mac, ip);
			// print local IP address:
			Serial.print("My IP address: ");
			Serial.println(Ethernet.localIP());
		}

		//init server
		Udp.begin(INPUT_PORT);
	}

	// Données Ethernet
	// An EthernetUDP instance to let us send and receive packets over UDP
	EthernetUDP Udp;
	bool use_dhcp = true;
	// buffers for receiving and sending data
	char packetBuffer[UDP_TX_PACKET_MAX_SIZE]; //buffer to hold incoming packet,
	char replyBuffer[UDP_TX_PACKET_MAX_SIZE];       // a string to send back
#endif

	/*
	------------------------------------------
	WIFI Shield
	------------------------------------------
	*/
#ifdef WIFI
	void InitialiseWifi(){
		//initialise les memebres    
		this->status = WL_IDLE_STATUS;
		this->ip = IPAddress(192, 168, 1, 177);
		strcpy(this->ssid, "AceTeaM"); //  your network SSID (name) 
		strcpy(this->pass, "emyleplusbeaudesbebes");    // your network password (use for WPA, or use as key for WEP)

		// check for the presence of the shield:
		if (WiFi.status() == WL_NO_SHIELD) {
			Serial.println("WiFi shield not present");
			// don't continue:
			while (true);
		}

		// attempt to connect to Wifi network:
		while (status != WL_CONNECTED) {
			Serial.print("Attempting to connect to SSID: ");
			Serial.println(ssid);
			// Connect to WPA/WPA2 network. Change this line if using open or WEP network:    
			this->status = WiFi.begin(ssid, pass);

			// wait 10 seconds for connection:
			//delay(10000);
		}

		long rssi = WiFi.RSSI();
		Serial.print("signal strength (RSSI):");
		Serial.print(rssi);
		Serial.println(" dBm");

		// print local IP address:
		Serial.print("My IP address: ");
		Serial.println(WiFi.localIP());

		//init server
		Udp.begin(INPUT_PORT);
	}

	// Données Wifi
private:
	int status;
	char ssid[256]; //  your network SSID (name) 
	char pass[256];    // your network password (use for WPA, or use as key for WEP)
	WiFiUDP Udp;
	//Adresse Physique de l'arduino (voir etiquette sur la carte)
	static const byte mac[];
	//Adresse IP fixe assigné à l'arduino (suivant de la passerelle)
	IPAddress ip;
	// buffers for receiving and sending data
	char packetBuffer[UDP_TX_PACKET_MAX_SIZE]; //buffer to hold incoming packet,
	char replyBuffer[UDP_TX_PACKET_MAX_SIZE];       // a string to send back
#endif
};

const byte ServerApp::mac[] = { 0x90, 0xA2, 0xDA, 0x0D, 0xB8, 0xE1 };

ServerApp app;

void setup() {
	app.Initialise();
}

void loop() {
    if(app.LireMessageTexte()){
      //..
    }
	/*
	char * buf;
	// if there's data available, read a packet
	int packetSize = Udp.parsePacket();
	if(packetSize)
	{
	Serial.print("Received packet of size ");
	Serial.println(packetSize);
	Serial.print("From ");
	IPAddress remote = Udp.remoteIP();
	for (int i =0; i < 4; i++)
	{
	Serial.print(remote[i], DEC);
	if (i < 3)
	{
	Serial.print(".");
	}
	}
	Serial.print(", port ");
	Serial.println(Udp.remotePort());

	// vérifie la limite du tempon
	if( packetSize >= UDP_TX_PACKET_MAX_SIZE ){
	Serial.print("Too big UDP packet");
	return;
	}

	// vérifie la limite du tempon
	if( packetSize > UDP_TX_PACKET_MAX_SIZE-1 )
	packetSize = UDP_TX_PACKET_MAX_SIZE-1;

	// read the packet into packetBufffer
	Udp.read(packetBuffer,UDP_TX_PACKET_MAX_SIZE);
	packetBuffer[packetSize] = 0;

	//parse la commande
	CMD cmd;
	memset(&cmd,0,sizeof(CMD));
	PTR mem = {packetBuffer,packetBuffer+sizeof(packetBuffer),packetBuffer};
	char name[80],*pname;
	char value[80],*pvalue;
	while(*mem.ptr != '\0'){
	xarg_decode_field(&mem,name,value);
	// supprime les eventuels Retour-Chariot '\r' ou saut de ligne '\n'
	pname = str_trimz(name);
	pvalue = str_trimz(value);
	//
	if(strcmp(name,"cmd")==0){
	if(strcmp(value,"on")==0){
	cmd.type = CMD_TYPE_SWITCH;
	}
	}
	else if(strcmp(name,"pin")==0){
	sscanf(value,"%d",&cmd.pin);
	}
	else if(strcmp(name,"val")==0){
	sscanf(value,"%d",&cmd.val);
	}
	}

	Serial.print("cmd=");
	Serial.println(cmd.type);
	Serial.print("pin=");
	Serial.println(cmd.pin);
	Serial.print("val=");
	Serial.println(cmd.val);

	//execute la commande
	switch(cmd.type){
	case CMD_TYPE_SWITCH:
	pinMode(cmd.pin, OUTPUT);
	digitalWrite(cmd.pin,(cmd.val ? HIGH : LOW));
	//resultat
	bptr(&mem,replyBuffer,sizeof(replyBuffer));
	xarg_encode_field(&mem,"error","ERR_OK");
	xarg_encode_field(&mem,"msg","SUCCESS");
	break;
	default:
	//resultat
	bptr(&mem,replyBuffer,sizeof(replyBuffer));
	xarg_encode_field(&mem,"error","ERR_FAILED");
	xarg_encode_field(&mem,"msg","UNKNOWN_CMD");
	break;
	}

	// send a reply, to the IP address and port that sent us the packet we received
	Udp.beginPacket(Udp.remoteIP(), OUTPUT_PORT);
	Udp.write(replyBuffer);
	Udp.endPacket();

	}*/
	delay(10);
}

