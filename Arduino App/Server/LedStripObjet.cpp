#include "LedStripObjet.h"
  
// Execute la commande
LedStripPinChangeEvent::LedStripPinChangeEvent(){
    this->self=0;
}

LedStripPinChangeEvent::LedStripPinChangeEvent(LedStripObjet*  ptr){
    this->self=ptr;
}

// Execute la commande
int LedStripPinChangeEvent::Executer(){
    if(self==0)
      return 0;
    Serial.println("LedStripPinChangeEvent::Executer");
      
    //réinitialise les membres
    self->ledValeur = LOW;
    self->curLed = 0;
    self->incLed = 1;
    
    // définit le mode des pins utilisés
    if(self->FirstPin.valeur && self->PinCount.valeur)
      for(int i=0; i<self->PinCount.valeur; i++)
        pinMode(self->FirstPin.valeur+i, OUTPUT);
     
    return 1;
}


// Lit la valeur du paramètre
int AnimationModeParam::LireValeur(const char* val){
      Serial.println("AnimationModeParam::LireValeur");
    byte old_valeur = this->valeur;  
    
    if(!ByteParam::LireValeur(val))
      return 0;
    
    if(this->valeur < 0 || this->valeur > 1)
    {
      this->valeur = old_valeur;//restore la valeur
      Serial.println("La valeur ne correspond pas ");
      return 0;
    }
    
    return 1;
}

// Constructeur
LedStripObjet::LedStripObjet() : Objet(){
  this->ledValeur = LOW;
  this->curLed = 0;
  this->incLed = 1;
  this->changeEvent = LedStripPinChangeEvent(this);
}

LedStripObjet::LedStripObjet(const char* id) : Objet(id){
  this->ledValeur = LOW;
  this->curLed = 0;
  this->incLed = 1;
  this->changeEvent = LedStripPinChangeEvent(this);
}

LedStripObjet::LedStripObjet(const char* id, byte firstPin, byte pinCount, byte mode) : Objet(id){
  this->ledValeur = LOW;
  this->curLed = 0;
  this->incLed = 1;
  this->changeEvent = LedStripPinChangeEvent(this);
  
  this->FirstPin       = ByteParam("FirstPin",firstPin);
  this->FirstPin.changeValeurEvent = &this->changeEvent;
  this->PinCount       = ByteParam("PinCount",pinCount);
  this->PinCount.changeValeurEvent = &this->changeEvent;
  this->AnimationMode  = AnimationModeParam("AnimationMode",mode);
  
  this->changeEvent.Executer();
}

int LedStripObjet::Etats(Parametre** list){
    return 0;
}

int LedStripObjet::Commandes(Commande** list){
    return 0;
}

int LedStripObjet::Configurations(Parametre** list){
    // Configuration
    list[0] = &this->FirstPin;
    list[1] = &this->PinCount;
    list[2] = &this->AnimationMode;
    return 3;
}

void LedStripObjet::Periode(){
  if(!this->FirstPin.valeur || !this->PinCount.valeur)
    return;

  if(this->AnimationMode.valeur == LEDSTRIP_MODE_LINEAR){
    for(int i=0; i<this->PinCount.valeur; i++)
        digitalWrite(this->FirstPin.valeur+i, this->ledValeur);
  
      this->ledValeur = (this->ledValeur == HIGH) ? LOW : HIGH;
  }
  if(this->AnimationMode.valeur == LEDSTRIP_MODE_DECALE){
      for(int i=0; i<this->PinCount.valeur; i++)
        digitalWrite(this->FirstPin.valeur+i, (this->curLed == i) ? HIGH : LOW);
  
      this->curLed += this->incLed;
      
      if(this->curLed>=this->PinCount.valeur){
        this->incLed=-1;
        this->curLed=this->PinCount.valeur-1;
        }
      if(this->curLed<0){
        this->incLed=1;
        this->curLed=0;
      }
  }
}


