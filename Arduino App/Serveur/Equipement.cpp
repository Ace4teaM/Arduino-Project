#include "Equipement.h"

// Constructeur
Equipement::Equipement(const char* id){
	this->id = crc32(0, id, strlen(id));
}

// Execute un message
int Equipement::ExecuterMessage(MessageTexte* message){
	Commande *cmd = 0;
	Parametre *cfg = 0;
	unsigned int id = 0;
	char valeur[MESSAGE_MAX_STRING];
	char* ofs = message->GetBuffer();

	if (0 == (ofs = message->LireSignature(ofs))){
		Serial.println("Signature invalide !");
		return 0;
	}

	unsigned int type, equipId, objetId;
	/*
	int type    = this->message.LireType(&ofs);
	int equipId = this->message.LireEquip(&ofs);
	int objetId = this->message.LireObjet(&ofs);
	*/
	if (0 == (ofs = message->LireCrc(ofs, 3, &type))){
		Serial.println("Invalid type");
		return 0;
	}

	ofs++; // ';'

	if (0 == (ofs = message->LireStrCrc(ofs, ';', &equipId)) || equipId != this->id){
		Serial.println("Invalid Equipment Id");
		return 0;
	}

	if (0 == (ofs = message->LireStrCrc(ofs, ';', &objetId))){
		Serial.println("Invalid Object Id");
		return 0;
	}

	Objet *objet = GetObjet(objetId);

	if (objet == 0){
		Serial.println("Object not found");
		return 0;
	}

	if (type == MessageTypeCommande){
		Serial.println("Read command");
		if (0 == (ofs = message->LireStrCrc(ofs, ';', &id))){
			Serial.println("Command not specified");
			return 0;
		}
		// obtient puis execute la commande
		cmd = objet->GetCommande(id);
		if (cmd != 0 && cmd->Executable(objet))
			return cmd->Executer(objet);

		Serial.println("Command not found");
		return 0;
	}
	else if (type == MessageTypeConfiguration){
		Serial.println("Read config");
		if (0 == (ofs = message->LireStrCrc(ofs, '=', &id))){
			Serial.println("Config not specified");
			return 0;
		}

		// obtient puis execute la commande
		cfg = objet->GetConfiguration(id);
		if (cfg != 0 && 0 != (ofs = message->LireTexte(ofs, ';', valeur))){
			return cfg->DefinirValeur(valeur);
		}

		Serial.println("Value not specified");
		return 0;
	}
	else if (type == MessageTypeEtat){
		Serial.println("Read state");
		return 0;
	}
	else{
		Serial.println("Unknown message type");
		return 0;
	}

	Serial.println("OK");
	return 1;

}

Objet* Equipement::GetObjet(unsigned int objetId){
	Objet* list[EQUIPEMENT_MAX_OBJET];
	int maxObjet = Objets(list);
	for (int x = 0; x<maxObjet; x++){
		if (list[x]->id == objetId)
			return list[x];
	}
	return 0;
}

