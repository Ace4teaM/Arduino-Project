#ifndef equipement_h
#define equipement_h
#include <Arduino.h>
#include <inttypes.h>
#include "Commande.h"

class Equipement{
public:
        Equipement();
        virtual int ExecuterCommande(Commande* cmd);
	virtual int LireMessageTexte();
	virtual void EcrireMessageTexte();
};

#endif
