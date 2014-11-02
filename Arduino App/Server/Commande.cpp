#include "Commande.h"

// Constructeur
Commande::Commande(const char* CodeCmd){
  this->id = crc32(0,CodeCmd,strlen(CodeCmd));
}


