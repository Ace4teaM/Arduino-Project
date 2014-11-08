#ifndef equipement_h
#define equipement_h
#include <Arduino.h>
#include <inttypes.h>
#include "Objet.h"

#define EQUIPEMENT_MAX_OBJET 10

class Equipement{
public:
	unsigned int id;//crc
public:
	Equipement(const char* id);
	// Obtient un objet par son identifiant
	Objet* GetObjet(unsigned int objetId);
	// Obtient la liste des objets
	virtual int Objets(Objet** list) = 0;
	// Lit un message sur le port serie
	virtual int LireMessageSerie(MessageTexte* msg) = 0;
	// Ecrit un message sur le port serie
	virtual void EcrireMessageSerie(MessageTexte* msg) = 0;
	// Execute un message
	virtual int ExecuterMessage(MessageTexte* message);
	// Execute une commande
	virtual void ExecuterCommande() = 0;
	// Execute une commande
	virtual void ExecuterConfiguration() = 0;
	// Evenement periodique
	virtual void Periode() = 0;
};

#endif
