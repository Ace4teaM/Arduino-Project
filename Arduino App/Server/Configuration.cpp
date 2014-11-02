#include "Configuration.h"

//constructeur
Configuration::Configuration(){
}

// lit les paramètres d'un message
int Configuration::LireParam(MessageTexte* message, char* ofs){
    char nom[256];
    char valeur[256];
    while((ofs=message->LireParam(ofs,nom,valeur)) != 0){
    }
    
    return 1;
}

