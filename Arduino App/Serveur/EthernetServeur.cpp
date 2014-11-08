#include "EthernetServeur.h"

EthernetServeur::EthernetServeur(const char* id) : Serveur(id) {
}

int EthernetServeur::InitialiseConnexion(const byte _mac[], const byte _ip[], bool dhcp){
	memcpy(this->mac, _mac, 6);
	memcpy(this->ip, _ip, 4);
	this->use_dhcp = dhcp;
}

int EthernetServeur::ConnexionReseau(){

	const byte gateway[] = { 192, 168, 1, 254 };
	const byte dns[] = { 192, 168, 1, 254 };

	Serial.print("MAC: ");
	Serial.print(this->mac[0], DEC);
	Serial.print(".");
	Serial.print(this->mac[1], DEC);
	Serial.print(".");
	Serial.print(this->mac[2], DEC);
	Serial.print(".");
	Serial.print(this->mac[3], DEC);
	Serial.print(".");
	Serial.print(this->mac[4], DEC);
	Serial.print(".");
	Serial.print(this->mac[5], DEC);
	Serial.println("...");

	if (use_dhcp){
		Serial.println("Attempting to connect to DHCP: ");
		if (Ethernet.begin(this->mac) == 0) {
			Serial.println("Failed to configure Ethernet using DHCP");
			return 0;
		}
	}
	else{
		Serial.print("Connect with static IP: ");
		Serial.print(ip[0], DEC);
		Serial.print(".");
		Serial.print(ip[1], DEC);
		Serial.print(".");
		Serial.print(ip[2], DEC);
		Serial.print(".");
		Serial.print(ip[3], DEC);
		Serial.println("...");

		Ethernet.begin(mac, ip, dns, gateway);
	}

	// print configuration
	Serial.print("My IP address: ");
	Serial.println(Ethernet.localIP());
	Serial.print("Input port: ");
	Serial.println(INPUT_PORT);
	Serial.print("Output port: ");
	Serial.println(OUTPUT_PORT);

	//init server
	Udp.begin(INPUT_PORT);
	return 1;
}

// Réceptionner un message texte sur le réseau
int EthernetServeur::LireMessageReseau(MessageTexte* message){
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
		*message = MessageTexte(this->packetBuffer, packetSize);

		return 1;
	}
	return 0;
}

// Envoyer un message texte sur le réseau
void EthernetServeur::EcrireMessageReseau(MessageTexte* message){
	// send a reply, to the IP address and port that sent us the packet we received
	Udp.beginPacket(Udp.remoteIP(), OUTPUT_PORT);
	Udp.write(message->GetBuffer());
	Udp.endPacket();
}