#ifndef serveur_h
#define serveur_h
#include <Arduino.h>
#include <inttypes.h>

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

#include "Equipement.h"

#define SERVEUR_MAX_EQUIPEMENT 4

// interface ethernet
#define INPUT_PORT 8888
#define OUTPUT_PORT 12345
#define USE_DHCP 1
#define UDP_TX_PACKET_MAX_SIZE 200

class Serveur : public Equipement{
public:
	//Adresse Physique de l'arduino (voir etiquette sur la carte)
	byte mac[6];
        IPAddress ip;
public:
        Serveur(const char* id, const byte mac[],const IPAddress* ip);
        // Obtient un equipement par son identifiant
        Equipement* GetEquipement(unsigned int equipId);
        // Obtient la liste des equipements
        virtual int Equipements(Equipement** list) = 0;
        // Lit un message sur le réseau
	virtual int LireMessageReseau(MessageTexte* message) = 0;
        // Ecrit un message sur le réseau
	virtual void EcrireMessageReseau(MessageTexte* message) = 0;
        // Connexion au réseau
	virtual int ConnexionReseau() = 0;
};

class EthernetServeur : public Serveur{
public:
	// Données Ethernet
	// An EthernetUDP instance to let us send and receive packets over UDP
	EthernetUDP Udp;
	bool use_dhcp;
	// buffers for receiving and sending data
	char packetBuffer[UDP_TX_PACKET_MAX_SIZE]; //buffer to hold incoming packet,
	char replyBuffer[UDP_TX_PACKET_MAX_SIZE];  // a string to send back
public:
        EthernetServeur(const char* id, const byte mac[],const IPAddress* ip);
        // Prepare la connexion
        int InitialiseConnexion(bool dhcp);
        // Lit un message sur le réseau
	virtual int LireMessageReseau(MessageTexte* message);
        // Ecrit un message sur le réseau
	virtual void EcrireMessageReseau(MessageTexte* message);
        // Connexion au réseau
	virtual int ConnexionReseau();
};

class WifiServeur : public Serveur{
public:
	int status;
	char ssid[256]; //  your network SSID (name) 
	char pass[256];    // your network password (use for WPA, or use as key for WEP)
	WiFiUDP Udp;
	//Adresse IP fixe assigné à l'arduino (suivant de la passerelle)
	IPAddress ip;
	// buffers for receiving and sending data
	char packetBuffer[UDP_TX_PACKET_MAX_SIZE]; //buffer to hold incoming packet,
	char replyBuffer[UDP_TX_PACKET_MAX_SIZE];       // a string to send back
public:
        WifiServeur(const char* id, const byte mac[],const IPAddress* ip);
        // Prepare la connexion
        int InitialiseConnexion(const char* ssid, const char* pass);
        // Lit un message sur le réseau
	virtual int LireMessageReseau(MessageTexte* message);
        // Ecrit un message sur le réseau
	virtual void EcrireMessageReseau(MessageTexte* message);
        // Connexion au réseau
	virtual int ConnexionReseau();
};

#endif
