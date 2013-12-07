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

/*

Test d'interface de communication réseau (client/Serveur)
Exemple de commande transmisible par paquet UDP (active la pin 9):  "cmd=on;pin=9;val=1;"

*/

#include <SPI.h>
#include <Ethernet.h>
#include <EthernetUdp.h>
#include <result.h>
#include <xarg.h>


//Adresse Physique de l'arduino (voir etiquette sur la carte)
byte mac[] = {  0x90, 0xA2, 0xDA, 0x0D, 0xB8, 0xE1 };
//Adresse IP fixe assigné à l'arduino (suivant de la paserelle)
IPAddress ip(192,168,1,177);

#define COM_PORT 8888 // HTTP
#define USE_DHCP 1
#define UDP_TX_PACKET_MAX_SIZE 200

// buffers for receiving and sending data
char packetBuffer[UDP_TX_PACKET_MAX_SIZE]; //buffer to hold incoming packet,
char ReplyBuffer[] = "acknowledged";       // a string to send back

// An EthernetUDP instance to let us send and receive packets over UDP
EthernetUDP Udp;

void setup() {
	// Open serial communications and wait for port to open:
	Serial.begin(9600);
	while (!Serial) {
		; // wait for serial port to connect. Needed for Leonardo only
	}


	// start the Ethernet connection and the server:
#ifndef USE_DHCP
	Ethernet.begin(mac, ip);
#else
	if (Ethernet.begin(mac) == 0) {
		Serial.println("Failed to configure Ethernet using DHCP");
		// no point in carrying on, so do nothing forevermore:
		for(;;)
			;
	}
#endif

	// print local IP address:
	Serial.print("My IP address: ");
	Serial.println(Ethernet.localIP());

	//init server
	Udp.begin(COM_PORT);
}

#define CMD_TYPE_NOP 0
#define CMD_TYPE_SWITCH 1
typedef struct _CMD{
	int type;
	int pin;
	int val;
}CMD;

typedef struct _EQUIPMENT{
	int id;
	int type;
	CMD* cmds;
}EQUIPMENT;


void loop() {
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
		const char* text=(const char*)packetBuffer;
		char name[80];
		char value[80];
		while(*text != '\0'){
			text = xarg_decode_field(text,name,value);

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
			break;
		default:
			Serial.println("unknown command");
			break;
		}

		// send a reply, to the IP address and port that sent us the packet we received
		Udp.beginPacket(Udp.remoteIP(), Udp.remotePort());
		Udp.write(ReplyBuffer);
		Udp.endPacket();

	}
	delay(10);
}

