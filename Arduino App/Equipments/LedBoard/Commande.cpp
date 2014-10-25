#include "Commande.h"

unsigned int LedBoardCmd::RandomizeOrder = crc32(0, "RAND", 4);
unsigned int LedBoardCmd::ResetOrder = crc32(0, "REST", 4);
        
// Constructeur
LedBoardCmd::LedBoardCmd() : Commande(){
  RaserParam();
}

// Réinitialise les paramètres
void LedBoardCmd::RaserParam(){
  Commande::RaserParam();
}

// Vérifie les paramètres
int LedBoardCmd::Valide(){
  Commande::Valide();
}

// Lit les paramètres d'un message
int LedBoardCmd::LireParam(MessageTexte* message, char* ofs){
    return Commande::LireParam();
}
