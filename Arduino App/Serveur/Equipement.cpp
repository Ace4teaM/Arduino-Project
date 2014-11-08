#include "Equipement.h"

// Constructeur
Equipement::Equipement(const char* id){
	this->id = crc32(0, id, strlen(id));
}

// Execute un message
// "[Type][EquipId];[ObjetId];..."
int Equipement::ExecuterMessage(MessageTexte* message){
	unsigned int id = 0;
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
		return objet->ExecuterCommande(message, ofs);
	}
	else if (type == MessageTypeConfiguration){
		return objet->ExecuterConfiguration(message, ofs);
	}
	else if (type == MessageTypeEtat){
		return objet->ExecuterEtat(message, ofs);
	}
	else{
		Serial.println("Unknown message type");
		return 0;
	}

	Serial.println("OK");
	return 1;

}

// Obtient un objet
Objet* Equipement::GetObjet(unsigned int objetId){
	Objet* list[EQUIPEMENT_MAX_OBJET];
	int maxObjet = Objets(list);
	for (int x = 0; x<maxObjet; x++){
		if (list[x]->id == objetId)
			return list[x];
	}
	return 0;
}

