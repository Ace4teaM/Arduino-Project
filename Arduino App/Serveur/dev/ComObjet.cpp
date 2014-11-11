#include "ComObjet.h"


// Constructeur
ComObjet::ComObjet() : Objet(){
	this->serial = 0;
	this->changePinEvent = new ComObjetPinChangeEvent(this);
}

ComObjet::ComObjet(const char* id) : Objet(id){
	this->serial = 0;
	this->changePinEvent = new ComObjetPinChangeEvent(this);
}

int ComObjet::Etats(Parametre** list){
	//Etats
	return 0;
}

int ComObjet::Commandes(Commande** list){
	//commandes
	return 0;
}

int ComObjet::Configurations(Parametre** list){
	// Configuration
	list[0] = &this->inPin;
	list[1] = &this->outPin;
	return 2;
}

void ComObjet::Periode(){
	LireMessage();
}

int ComObjet::LireMessage(){
	int packetSize = 0;

	// Lit les données du port série
	if (Serial.available()){
		packetSize = this->serial->readBytesUntil(COMOBJET_SERIAL_AND_OF_STRING_CHAR, this->serialBuffer, COMOBJET_SERIAL_BUFFER_MAX_SIZE - 1);
	}

	// initialise le message
	if (packetSize){
		Serial.print("Received packet of size ");
		Serial.print(packetSize, DEC);
		Serial.println(" from serial");
		serialBuffer[packetSize] = 0;
		Serial.println(serialBuffer);

		// initialise le message actuel
		this->msg = MessageTexte(this->serialBuffer, packetSize);

		return 1;
	}

	return 0;
}


// Execute la commande
ComObjetPinChangeEvent::ComObjetPinChangeEvent(){
	this->obj = 0;
}

ComObjetPinChangeEvent::ComObjetPinChangeEvent(ComObjet*  ptr){
	ComObjetPinChangeEvent();
	this->obj = ptr;
}

// Execute la commande
int ComObjetPinChangeEvent::Executer(){
	if (obj == 0)
		return 0;

	//Initialise l'objet
	if (obj->inPin.valeur != 0 && obj->outPin.valeur != 0){
		if (obj->serial == 0)//alloue une premiere fois
			obj->serial = new SoftwareSerial(obj->inPin.valeur, obj->outPin.valeur); // RX, TX
		else
			*obj->serial = SoftwareSerial(obj->inPin.valeur, obj->outPin.valeur); // RX, TX
		obj->serial->begin(4800);
	}

	return 1;
}
