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
// Note: Terminer la chaine par le caractère de fin '$' pour optimiser la detection de fin de chaine
int Serveur::LireMessageSerie(MessageTexte* msg){
	int packetSize=0;

	// Lit les données du port série
	if (Serial.available()){
		packetSize = Serial.readBytesUntil(SERIAL_AND_OF_STRING_CHAR, this->serialBuffer, SERIAL_BUFFER_MAX_SIZE-1);
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
void Serveur::EcrireMessageSerie(MessageTexte* msg){
	Serial.print(msg->GetBuffer());
}
