#ifndef LedStripEquipement_h
#define LedStripEquipement_h
#include <Arduino.h>
#include <inttypes.h>
#include "Equipement.h"
#include "LedStripObjet.h"

class LedStripEquipement : public Equipement{
public:
	LedStripEquipement() : Equipement("LedStrip"){}
public:
	// objets
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
};

#endif
