#include "Serveur.h"

// Constructeur
Serveur::Serveur(const char* id) : Equipement(id){
	//memcpy(this->mac, _mac, 6); //not work
	//memcpy(this->ip, _ip, 4);

	/*this->mac[0] = 0xDE;
	this->mac[1] = 0xAD;
	this->mac[2] = 0xBE;
	this->mac[3] = 0xEF;
	this->mac[4] = 0xFE;
	this->mac[5] = 0xED;*/
}

Equipement* Serveur::GetEquipement(unsigned int equipId){
	Equipement* list[SERVEUR_MAX_EQUIPEMENT];
	int maxEquip = Equipements(list);
	for (int x = 0; x<maxEquip; x++){
		if (list[x]->id == equipId)
			return list[x];
	}
	return 0;
}

// Lit un message sur le port serie
int Serveur::LireMessageSerie(MessageTexte* msg){
	return 0;
}

// Ecrit un message sur le port serie
void Serveur::EcrireMessageSerie(MessageTexte* msg){
}
