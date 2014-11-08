#ifndef serveur_h
#define serveur_h
#include <Arduino.h>
#include <inttypes.h>

#include "Equipement.h"

#define SERVEUR_MAX_EQUIPEMENT 4

class Serveur : public Equipement{
protected:
	//Adresse Physique de l'arduino (voir etiquette sur la carte)
	byte mac[6];
	//Adresse Statique de l'arduino (optionnelle)
	byte ip[4];
public:
	Serveur(const char* id);
	// Obtient un equipement par son identifiant
	Equipement* GetEquipement(unsigned int equipId);
	// Obtient la liste des equipements
	virtual int Equipements(Equipement** list) = 0;
	// Lit un message sur le réseau
	virtual int LireMessageReseau(MessageTexte* message) = 0;
	// Ecrit un message sur le réseau
	virtual void EcrireMessageReseau(MessageTexte* message) = 0;
	// Lit un message sur le port serie
	virtual int LireMessageSerie(MessageTexte* msg);
	// Ecrit un message sur le port serie
	virtual void EcrireMessageSerie(MessageTexte* msg);
	// Execute une commande
	virtual void ExecuterCommande();
	// Execute une commande
	virtual void ExecuterConfiguration();
	// Connexion au réseau
	virtual int ConnexionReseau() = 0;
};

#endif
