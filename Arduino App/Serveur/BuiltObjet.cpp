#include "BuiltObjet.h"


// Constructeur
BuiltObjet::BuiltObjet() : Objet(){
}

BuiltObjet::BuiltObjet(const char* id) : Objet(id){
}

int BuiltObjet::Etats(Parametre** list){
	//Etats
	return 0;
}

int BuiltObjet::Commandes(Commande** list){
	//commandes
	list[0] = (Commande*)&this->LedOn;
	list[1] = (Commande*)&this->LedOff;
	return 2;
}

int BuiltObjet::Configurations(Parametre** list){
	// Configuration
	return 0;
}

void BuiltObjet::Periode(){
}


// Constructeur
BuiltLedOffCmd::BuiltLedOffCmd() : Commande("Off"){
}

// Vérifie si la commande est executable
int BuiltLedOffCmd::Executable(Objet* objet){
	return 1;
}

// Execute la commande
int BuiltLedOffCmd::Executer(Objet* objet){
	digitalWrite(LED_BUILTIN, LOW);
	return 1;
}


// Constructeur
BuiltLedOnCmd::BuiltLedOnCmd() : Commande("On"){
}

// Vérifie si la commande est executable
int BuiltLedOnCmd::Executable(Objet* objet){
	return 1;
}

// Execute la commande
int BuiltLedOnCmd::Executer(Objet* objet){
	digitalWrite(LED_BUILTIN, HIGH);
	return 1;
}

