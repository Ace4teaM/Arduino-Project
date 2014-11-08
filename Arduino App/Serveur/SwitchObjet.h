#ifndef switchobjet_h
#define switchobjet_h
#include <Arduino.h>
#include <inttypes.h>
#include "Objet.h"

class SwitchOnCmd : public Commande{
public:
	// Constructeur
	SwitchOnCmd();
	virtual int Executer(Objet* objet);
	virtual int Executable(Objet* objet);
};

class SwitchOffCmd : public Commande{
public:
	// Constructeur
	SwitchOffCmd();
	virtual int Executer(Objet* objet);
	virtual int Executable(Objet* objet);
};

class SwitchObjet : public Objet{
public:
	// Configuration
	ByteParam PushPin;
	ByteParam StatePin;
	// Etats
	BitParam PushState;
	// Commandes
	SwitchOnCmd OnCmd;
	SwitchOffCmd OffCmd;
public:
	SwitchObjet();
	SwitchObjet(const char* id);
	SwitchObjet(const char* id, byte pushPin, byte statePin);
	virtual int Etats(Parametre** list);
	virtual int Commandes(Commande** list);
	virtual int Configurations(Parametre** list);
	// Evenement periodique
	virtual void Periode();
};

#endif
