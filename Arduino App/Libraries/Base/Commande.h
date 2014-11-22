#ifndef commande_h
#define commande_h
#include <Arduino.h>
#include <inttypes.h>
#include "Message.h"
#include "CRC32.h"
#include "Objet.h"

class Objet;

class Commande{
public:
	unsigned int id;
public:
	// Constructeur
	Commande(const char* CodeCmd);
	virtual int Executer(Objet* objet) = 0;
	virtual int Executable(Objet* objet) = 0;
};


#endif
