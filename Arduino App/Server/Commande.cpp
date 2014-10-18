#include "Commande.h"

//constructeur
Commande::Commande(){
  this->EquipId = -1;
  this->CodeCmd[0] = 0;
}

// lit les paramètres d'un message
int Commande::LireParam(MessageTexte* message, char* ofs){
    char nom[256];
    char valeur[256];
    while((ofs=message->LireParam(ofs,nom,valeur)) != 0){
      if(nom[0]=='E' && strcmp(nom,"EQUIPID")==0)
        sscanf(valeur,"%d",&this->EquipId);
      if(nom[0]=='C' && strcmp(nom,"CODECMD")==0)
        strncpy(this->CodeCmd,valeur,sizeof(this->CodeCmd));
    }
    
    return 1;
}
