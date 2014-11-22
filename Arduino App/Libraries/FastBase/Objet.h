#ifndef objet_h
#define objet_h
#include <Arduino.h>
#include <inttypes.h>
#include "Parametre.h"
#include "Commande.h"

#define OBJET_MAX_ETAT 10
#define OBJET_MAX_CMD  10
#define OBJET_MAX_CFG  10

class Commande;

class Objet{
public:
	unsigned int id;
public:
	Objet();
	Objet(const char* id);
	inline virtual unsigned int GetType(){ return crc32("Objet"); }
	virtual int Etats(Parametre** list) = 0;
	virtual int Commandes(Commande** list) = 0;
	virtual int Configurations(Parametre** list) = 0;
	virtual void Periode() = 0;
	// Obtient une commande par son identifiant
	Commande* GetCommande(unsigned int Id);
	// Obtient un parametre de configuration par son identifiant
	Parametre* GetConfiguration(unsigned int Id);
	// Execute une commande
	virtual int ExecuterCommande(MessageTexte* message, char* ofs /*, MessageTexte* responseMessage, char* responseOfs*/);
	// Execute une commande
	virtual int ExecuterConfiguration(MessageTexte* message, char* ofs /*, MessageTexte* responseMessage, char* responseOfs*/);
	// Execute un état
	virtual int ExecuterEtat(MessageTexte* message, char* ofs /*, MessageTexte* responseMessage, char* responseOfs*/);
};

#endif
