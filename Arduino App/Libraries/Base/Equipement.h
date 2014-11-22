#ifndef equipement_h
#define equipement_h
#include <Arduino.h>
#include <inttypes.h>
#include "Objet.h"

#define EQUIPEMENT_MAX_OBJET 10
#define SERIAL_BUFFER_MAX_SIZE 128
#define SERIAL_AND_OF_STRING_CHAR '$'

class Equipement{
public:
	unsigned int id;//crc
	// Tampon du port serie
	char serialBuffer[SERIAL_BUFFER_MAX_SIZE];
public:
	Equipement(const char* id);
	// Obtient un objet par son identifiant
	Objet* GetObjet(unsigned int objetId);
	// Initialise le port serie
	void InitialiseSerie();
	// Obtient la liste des objets
	virtual int Objets(Objet** list) = 0;
	// Lit un message sur le port serie
	virtual int LireMessageSerie(MessageTexte* msg);
	// Ecrit un message sur le port serie
	virtual void EcrireMessageSerie(MessageTexte* msg);
	// Execute un message
	virtual int ExecuterMessage(MessageTexte* message);
	// Evenement periodique
	virtual void Periode() = 0;
};

#endif
