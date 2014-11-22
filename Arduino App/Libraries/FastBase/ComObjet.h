#ifndef comobjet_h
#define comobjet_h
#include <Arduino.h>
#include <inttypes.h>
#include <SoftwareSerial.h>
#include <Objet.h>

#define COMOBJET_SERIAL_BUFFER_MAX_SIZE 64
#define COMOBJET_SERIAL_AND_OF_STRING_CHAR '$'

class ComObjet : public Objet{
public:
	unsigned int equipId;
	SoftwareSerial* serial;
	Evenement* changePinEvent;
	char serialBuffer[COMOBJET_SERIAL_BUFFER_MAX_SIZE];
	MessageTexte message;
	bool serialReady,messageReady;
public:
	// Configuration
	ByteParam rxPin;
	ByteParam txPin;
	// Etats
	//...
	// Commandes
	//...
public:
	ComObjet();
	ComObjet(const char* id, const char* equipId);
	ComObjet(const char* id, const char* equipId, byte rxPin, byte txPin);
	inline virtual unsigned int GetType(){ return crc32("ComObjet"); }
	virtual int Etats(Parametre** list);
	virtual int Commandes(Commande** list);
	virtual int Configurations(Parametre** list);
	// Evenement periodique
	virtual void Periode();
	//methodes
	int LireMessage();
	int InitialiseSerie();
};

class ComObjetPinChangeEvent : public Evenement{
public:
	ComObjet* obj;
	ComObjetPinChangeEvent();
	ComObjetPinChangeEvent(ComObjet* ptr);
	virtual int Executer();
};


#endif
