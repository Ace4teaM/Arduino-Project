#include "SwitchObjet.h"

// Constructeur
SwitchObjet::SwitchObjet() : Objet(){
}

SwitchObjet::SwitchObjet(const char* id) : Objet(id){
	this->PushState = BitParam("PushState", 0);
}

SwitchObjet::SwitchObjet(const char* id, byte pushPin, byte statePin) : Objet(id){
	this->PushState = BitParam("PushState", 0);
	this->PushPin = ByteParam("PushPin", pushPin);
	this->StatePin = ByteParam("StatePin", statePin);
	if (pushPin)
		pinMode(pushPin, OUTPUT);
	if (statePin)
		pinMode(statePin, INPUT);
}

int SwitchObjet::Etats(Parametre** list){
	//Etats
	list[0] = &this->PushState;
	return 1;
}

int SwitchObjet::Commandes(Commande** list){
	//commandes
	list[0] = &this->OnCmd;
	list[1] = &this->OffCmd;
	return 2;
}

int SwitchObjet::Configurations(Parametre** list){
	// Configuration
	list[0] = &this->PushPin;
	list[1] = &this->StatePin;
	return 2;
}

void SwitchObjet::Periode(){
}


// Constructeur
SwitchOnCmd::SwitchOnCmd() : Commande("On"){
}

// Vérifie si la commande est executable
int SwitchOnCmd::Executable(Objet* objet){
	SwitchObjet* switchObj = (SwitchObjet*)objet;
	if (switchObj != 0 && switchObj->PushPin.valeur >= 0 && switchObj->PushPin.valeur < NUM_DIGITAL_PINS)
		return 1;
	return 0;
}

// Execute la commande
int SwitchOnCmd::Executer(Objet* objet){
	SwitchObjet* switchObj = (SwitchObjet*)objet;
	digitalWrite(switchObj->PushPin.valeur, HIGH);

	Serial.print("Write HIGH to pin ");
	Serial.println(switchObj->PushPin.valeur);

	return 1;
}


// Constructeur
SwitchOffCmd::SwitchOffCmd() : Commande("Off"){
}

// Vérifie si la commande est executable
int SwitchOffCmd::Executable(Objet* objet){
	SwitchObjet* switchObj = (SwitchObjet*)objet;
	if (switchObj != 0 && switchObj->PushPin.valeur >= 0 && switchObj->PushPin.valeur < NUM_DIGITAL_PINS)
		return 1;
	return 0;
}

// Execute la commande
int SwitchOffCmd::Executer(Objet* objet){
	SwitchObjet* switchObj = (SwitchObjet*)objet;
	digitalWrite(switchObj->PushPin.valeur, LOW);
	return 1;
}


