#include "Equipement.h"

// Constructeur
Equipement::Equipement(const char* id){
	this->id = crc32(0, id, strlen(id));
}

void Equipement::InitialiseSerie(){
	// Open serial communications and wait for port to open:
	Serial.begin(9600);
	while (!Serial) {
		; // wait for serial port to connect. Needed for Leonardo only
	}
}

// Lit un message sur le port serie
// Note: Terminer la chaine par le caractère de fin '$' pour optimiser la detection de fin de chaine
int Equipement::LireMessageSerie(MessageTexte* msg){
	int packetSize = 0;

	// Lit les données du port série
	if (Serial.available()){
		packetSize = Serial.readBytesUntil(SERIAL_AND_OF_STRING_CHAR, this->serialBuffer, SERIAL_BUFFER_MAX_SIZE - 1);
	}

	// initialise le message
	if (packetSize){
		Serial.print("Received packet of size ");
		Serial.print(packetSize, DEC);
		Serial.println(" from serial");
		serialBuffer[packetSize] = 0;
		Serial.println(serialBuffer);

		// initialise le message actuel
		*msg = MessageTexte(this->serialBuffer, packetSize);

		return 1;
	}

	return 0;
}

// Ecrit un message sur le port serie
void Equipement::EcrireMessageSerie(MessageTexte* msg){
	Serial.print(msg->GetBuffer());
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

