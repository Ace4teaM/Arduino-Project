#ifndef comobjet_h
#define comobjet_h
#include <Arduino.h>
#include <inttypes.h>
#include <SoftwareSerial.h>
#include "Objet.h"

#define COMOBJET_SERIAL_BUFFER_MAX_SIZE 128
#define COMOBJET_SERIAL_AND_OF_STRING_CHAR '$'

class ComObjet : public Objet{
public:
	SoftwareSerial* serial;
	Evenement* changePinEvent;
	char serialBuffer[COMOBJET_SERIAL_BUFFER_MAX_SIZE];
	MessageTexte msg;
public:
	// Configuration
	ByteParam inPin;
	ByteParam outPin;
	// Etats
	//...
	// Commandes
	//...
public:
	ComObjet();
	ComObjet(const char* id);
	virtual int Etats(Parametre** list);
	virtual int Commandes(Commande** list);
	virtual int Configurations(Parametre** list);
	// Evenement periodique
	virtual void Periode();
	//methodes
	int LireMessage();
};

class ComObjetPinChangeEvent : public Evenement{
public:
	ComObjet* obj;
	ComObjetPinChangeEvent();
	ComObjetPinChangeEvent(ComObjet* ptr);
	virtual int Executer();
};


#endif
