#include "WifiServeur.h"

WifiServeur::WifiServeur(const char* id) : Serveur(id){
}

int WifiServeur::InitialiseConnexion(const byte _mac[], const byte _ip[], const char* wifi_ssid, const char* wifi_pass){
	//initialise les membres
	memcpy(this->mac, _mac, 6);
	memcpy(this->ip, _ip, 4);
	this->status = WL_IDLE_STATUS;
	strcpy(this->ssid, wifi_ssid); //  your network SSID (name) 
	strcpy(this->pass, wifi_pass); // your network password (use for WPA, or use as key for WEP)

	// check for the presence of the shield:
	if (WiFi.status() == WL_NO_SHIELD) {
		Serial.println("WiFi shield not present");
		return 0;
	}
	return 1;
}

int WifiServeur::ConnexionReseau(){

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

	// print configuration
	Serial.print("My IP address: ");
	Serial.println(WiFi.localIP());
	Serial.print("Input port: ");
	Serial.println(INPUT_PORT);
	Serial.print("Output port: ");
	Serial.println(OUTPUT_PORT);

	//init server
	Udp.begin(INPUT_PORT);
	return 1;
}


// Réceptionner un message texte sur le réseau
int WifiServeur::LireMessageReseau(MessageTexte* message){
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
void WifiServeur::EcrireMessageReseau(MessageTexte* message){
	// send a reply, to the IP address and port that sent us the packet we received
	Udp.beginPacket(Udp.remoteIP(), OUTPUT_PORT);
	Udp.write(message->GetBuffer());
	Udp.endPacket();
}