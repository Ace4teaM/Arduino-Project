#include "Objet.h"

// Constructeur
Objet::Objet(){
	this->id = 0;
}

Objet::Objet(const char* id){
	this->id = crc32(0, id, strlen(id));
}

Commande* Objet::GetCommande(unsigned int Id){
	Commande* list[OBJET_MAX_CMD];
	int maxCmd = Commandes(list);
	for (int x = 0; x<maxCmd; x++){
		if (list[x]->id == Id)
			return list[x];
	}
	return 0;
}

Parametre* Objet::GetConfiguration(unsigned int Id){
	Parametre* list[OBJET_MAX_CFG];
	int maxCfg = Configurations(list);
	for (int x = 0; x<maxCfg; x++){
		if (list[x]->id == Id)
			return list[x];
	}
	return 0;
}
