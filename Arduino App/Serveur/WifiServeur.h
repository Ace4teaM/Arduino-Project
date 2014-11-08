#ifndef wifiserveur_h
#define wifiserveur_h
#include <Arduino.h>
#include <inttypes.h>

#include <SPI.h>
#include <WiFi.h>
#include <WiFiClient.h>
#include <WiFiServer.h>
#include <WiFiUdp.h>

#include "Serveur.h"

// interface ethernet
#define INPUT_PORT 8888
#define OUTPUT_PORT 12345
#define USE_DHCP 1
#define UDP_TX_PACKET_MAX_SIZE 200

class WifiServeur : public Serveur{
public:
	int status;
	char ssid[256]; //  your network SSID (name) 
	char pass[256];    // your network password (use for WPA, or use as key for WEP)
	WiFiUDP Udp;
	// buffers for receiving and sending data
	char packetBuffer[UDP_TX_PACKET_MAX_SIZE]; //buffer to hold incoming packet,
	char replyBuffer[UDP_TX_PACKET_MAX_SIZE];       // a string to send back
public:
	WifiServeur(const char* id);
	// Prepare la connexion
	int InitialiseConnexion(const byte mac[], const byte ip[], const char* ssid, const char* pass);
	// Lit un message sur le réseau
	virtual int LireMessageReseau(MessageTexte* message);
	// Ecrit un message sur le réseau
	virtual void EcrireMessageReseau(MessageTexte* message);
	// Connexion au réseau
	virtual int ConnexionReseau();
};

#endif
