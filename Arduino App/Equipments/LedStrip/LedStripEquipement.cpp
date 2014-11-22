#include "LedStripEquipement.h"

/*
------------------------------------------
Methodes
------------------------------------------
*/

// Initialise
void LedStripEquipement::Initialise(){
	this->InitialiseSerie();
	this->InitialiseObjets();
}

// Execute 
void LedStripEquipement::Periode(){
	//actualise les objets
	for (int i = 0; i<nObjets; i++)
	  this->pObjets[i]->Periode();

	//execute les messages series (USB)
	MessageTexte message;
	if (this->LireMessageSerie(&message))
	  this->ExecuterMessage(&message);

#ifdef COM
            // test
            /*if(strcmp(message.GetBuffer(),"test")==0){
              if(this->com.serialReady == false)
                Serial.println("Com not ready !");
              else if(this->com.serial != 0){
                Serial.println("Test send message");
                this->com.serial->println("test");
              }
            }*/

            //execute les messages series
            if(this->com.messageReady == true){
              this->ExecuterMessage(&this->com.message);
              this->com.messageReady = false; // permet la reception d'un nouveau message
            }
#endif
}

// Obtient la liste des objets
int LedStripEquipement::Objets(Objet** list){
	int i = 0;

	// ledstrip
	list[i++] = &strip;

#ifdef COM
        // communication
        list[i++] = &com;
#endif

	return i;
}

void LedStripEquipement::InitialiseObjets(){
	Serial.println("Initialize objects...");

	this->strip = LedStripObjet("strip", 2, 5, LEDSTRIP_MODE_DECALE);

#ifdef COM
        this->com = ComObjet("com","root",10,11); // RX, TX
#endif

	this->nObjets = Objets(this->pObjets);
}

