#include "LedStripEquipement.h"

/*
------------------------------------------
Methodes
------------------------------------------
*/

// Initialise
void LedStripEquipement::Initialise(){
	this->InitialiseSerie();
	this->InitialiseObjets();
}

// Execute 
void LedStripEquipement::Periode(){
	//actualise les objets
	for (int i = 0; i<nObjets; i++)
		this->pObjets[i]->Periode();
	//execute les messages series
	MessageTexte message;
	if (this->LireMessageSerie(&message))
		this->ExecuterMessage(&message);
}

// Obtient la liste des objets
int LedStripEquipement::Objets(Objet** list){
	int i = 0;

	// ledstrip
	list[i++] = &strip;

	return i;
}

void LedStripEquipement::InitialiseObjets(){
	Serial.println("Initialize objects...");

	this->strip = LedStripObjet("strip", 2, 5, LEDSTRIP_MODE_DECALE);

	this->nObjets = Objets(this->pObjets);
}

