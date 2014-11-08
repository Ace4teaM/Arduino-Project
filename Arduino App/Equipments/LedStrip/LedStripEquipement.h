#ifndef LedStripEquipement_h
#define LedStripEquipement_h
#include <Arduino.h>
#include <inttypes.h>
#include "Equipement.h"
#include "SwitchObjet.h"
#include "LedStripObjet.h"

class LedStripEquipement : public Equipement{
  public:
	LedStripEquipement() : Equipement("LedStrip"){}
  public:
        // objets
        SwitchObjet led[4];
        LedStripObjet strip;
        
        // liste des objets
        Objet* pObjets[EQUIPEMENT_MAX_OBJET];
        int nObjets;

	/*
	------------------------------------------
	Methodes
	------------------------------------------
	*/

	// Initialise
	void Initialise();

        // Execute 
	void Periode();

        // Obtient la liste des objets
        int Objets(Objet** list);
        
        // Initialise la liste des objets
	void InitialiseObjets();

        // Lit un message sur le port serie
	int LireMessageSerie(MessageTexte* msg);

        // Ecrit un message sur le port serie
	void EcrireMessageSerie(MessageTexte* msg);

        // Execute une commande
	void ExecuterCommande();

        // Execute une commande
	void ExecuterConfiguration();
};

#endif
