#ifndef commande_h
#define commande_h
#include <Arduino.h>
#include <inttypes.h>
#include "Message.h"

class Commande{
public:
	char CodeCmd[128];
	int EquipId;
public:
        Commande();
        // lit les paramètres d'un message
        int LireParam(MessageTexte* message, char* ofs);
};

#endif
