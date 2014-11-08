#ifndef ethernetserveur_h
#define ethernetserveur_h
#include <Arduino.h>
#include <inttypes.h>

#include <Dhcp.h>
#include <Dns.h>
#include <Ethernet.h>
#include <EthernetClient.h>
#include <EthernetServer.h>
#include <EthernetUdp.h>
#include <util.h>

#include "Serveur.h"

// interface ethernet
#define INPUT_PORT 8888
#define OUTPUT_PORT 12345
#define USE_DHCP 1
#define UDP_TX_PACKET_MAX_SIZE 200

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
	EthernetServeur(const char* id);
	// Prepare la connexion
	int InitialiseConnexion(const byte mac[], const byte ip[],bool dhcp);
	// Lit un message sur le réseau
	virtual int LireMessageReseau(MessageTexte* message);
	// Ecrit un message sur le réseau
	virtual void EcrireMessageReseau(MessageTexte* message);
	// Connexion au réseau
	virtual int ConnexionReseau();
};

#endif
