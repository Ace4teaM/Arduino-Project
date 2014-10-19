#include "Commande.h"

unsigned int Commande::DigitalOut = crc32(0, "DOUT", 4);
unsigned int Commande::DigitalIn = crc32(0, "DIN", 3);
unsigned int Commande::AnalogOut = crc32(0, "AOUT", 4);
unsigned int Commande::AnalogIn = crc32(0, "AIN", 3);
unsigned int Commande::LedHigh = crc32(0, "LEDH", 4);
unsigned int Commande::LedLow = crc32(0, "LEDL", 4);
        
// Constructeur
Commande::Commande(){
  RaserParam();
}

// Réinitialise les paramètres
void Commande::RaserParam(){
  this->EquipId = -1;
  this->CodeCmd = 0;
}

// Vérifie les paramètres
int Commande::Valide(){
  return (this->CodeCmd != 0) ? 1 : 0;
}

// Lit les paramètres d'un message
int Commande::LireParam(MessageTexte* message, char* ofs){
    char nom[256];
    char valeur[256];
    
    this->RaserParam();
    
    while((ofs=message->LireParam(ofs,nom,valeur)) != 0){
      if(nom[0]=='E' && strcmp(nom,"EQUIPID")==0)
        sscanf(valeur,"%d",&this->EquipId);
      if(nom[0]=='C' && strcmp(nom,"CODECMD")==0)
        this->CodeCmd = crc32(0, valeur, strlen(valeur));
      if(nom[0]=='P' && strcmp(nom,"PINNUM")==0)
        sscanf(valeur,"%d",&this->PinNum);
      if(nom[0]=='V' && strcmp(nom,"VALUE")==0)
        sscanf(valeur,"%d",&this->Value);
    }
    
    return 1;
}
