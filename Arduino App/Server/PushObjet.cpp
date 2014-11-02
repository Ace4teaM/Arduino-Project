#include "PushObjet.h"


// Constructeur
PushObjet::PushObjet() : Objet(){
}
PushObjet::PushObjet(const char* id, byte pushPin) : Objet(id){
  this->m_PushPin   = ByteParam("PushPin",pushPin);
}

int PushObjet::Etats(Parametre** list){
    //Etats
    return 0;
}

int PushObjet::Commandes(Commande** list){
    //commandes
    list[0] = &this->m_PushCmd;
    return 1;
}

int PushObjet::Configurations(Parametre** list){
    // Configuration
    list[0] = &this->m_PushPin;
    return 1;
}

void PushObjet::Periode(){
}



// Constructeur
PushCmd::PushCmd() : Commande("Push"){
}

// Vérifie si la commande est executable
int PushCmd::Executable(Objet* objet){
  PushObjet* pushObj = (PushObjet*)objet;
  if(pushObj != 0 && pushObj->m_PushPin.valeur >= 0 && pushObj->m_PushPin.valeur < NUM_DIGITAL_PINS)
    return 1;
  return 0;
}

// Execute la commande
int PushCmd::Executer(Objet* objet){
    PushObjet* pushObj = (PushObjet*)objet;
    digitalWrite(pushObj->m_PushPin.valeur, HIGH);
    return 1;
}


