#include "ComObjet.h"


// Constructeur
ComObjet::ComObjet() : Objet(){
	this->serial = 0;
	this->serialReady = false;
	this->messageReady = false;
	this->changePinEvent = new ComObjetPinChangeEvent(this);
}

ComObjet::ComObjet(const char* id) : Objet(id){
	this->serial = 0;
	this->serialReady = false;
	this->messageReady = false;
	this->changePinEvent = new ComObjetPinChangeEvent(this);

	this->rxPin = ByteParam("RxPin", -1);
	this->rxPin.changeValeurEvent = this->changePinEvent;
	this->txPin = ByteParam("TxPin", -1);
	this->txPin.changeValeurEvent = this->changePinEvent;
}


ComObjet::ComObjet(const char* id, byte rxPin, byte txPin) : Objet(id){
	this->serial = 0;
	this->serialReady = false;
	this->messageReady = false;
	this->changePinEvent = new ComObjetPinChangeEvent(this);

	this->rxPin = ByteParam("RxPin", rxPin);
	this->rxPin.changeValeurEvent = this->changePinEvent;
	this->txPin = ByteParam("TxPin", txPin);
	this->txPin.changeValeurEvent = this->changePinEvent;

	this->InitialiseSerie();
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
	list[0] = &this->rxPin;
	list[1] = &this->txPin;
	return 2;
}

void ComObjet::Periode(){
	if (this->serialReady == true && this->messageReady == false)
		this->LireMessage();
}

int ComObjet::LireMessage(){
	int packetSize = 0;

	// Lit les données du port série
	if (this->serial->available()){
		packetSize = this->serial->readBytesUntil(COMOBJET_SERIAL_AND_OF_STRING_CHAR, this->serialBuffer, COMOBJET_SERIAL_BUFFER_MAX_SIZE - 1);
	}

	// initialise le message
	if (packetSize){
		Serial.print("Received packet of size ");
		Serial.print(packetSize, DEC);
		Serial.println(" from Rx/Tx");
		serialBuffer[packetSize] = 0;
		Serial.println(serialBuffer);

		// initialise le message actuel
		this->message = MessageTexte(this->serialBuffer, packetSize);
		this->messageReady = true;

		return 1;
	}

	return 0;
}

// Execute la commande
int ComObjet::InitialiseSerie(){
	Serial.println("InitialiseSerie");
	//Initialise l'objet
	if (this->rxPin.valeur != -1 && this->txPin.valeur != -1){
		Serial.print("rxPin=");
		Serial.println(this->rxPin.valeur, DEC);
		Serial.print("txPin=");
		Serial.println(this->txPin.valeur, DEC);

		if (this->serial == 0)
			this->serial = new SoftwareSerial(this->rxPin.valeur, this->txPin.valeur); // RX, TX
		else
			*this->serial = SoftwareSerial(this->rxPin.valeur, this->txPin.valeur); // RX, TX
		this->serial->begin(4800);//115200
		this->serialReady = true;

		Serial.println("ComObjet ready !");
	}
	else
		this->serialReady = false;

	return 1;
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

	//Initialise la communication
	obj->InitialiseSerie();

	return 1;
}
