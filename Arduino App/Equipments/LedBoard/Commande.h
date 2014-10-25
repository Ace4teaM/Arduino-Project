#ifndef commande_h
#define commande_h
#include <Arduino.h>
#include <inttypes.h>
#include "Message.h"
#include "CRC32.h"

class LedBoardCmd : public Commande{
public:
        // liste de codes commandes
        static unsigned int RandomizeOrder; // RAND
        static unsigned int ResetOrder;  // REST
public:
        // Constructeur
        LedBoardCmd();
        // Lit les paramètres d'un message
        int LireParam(MessageTexte* message, char* ofs);
        // Réinitialise les paramètres
        void RaserParam();
        // Vérifie les paramètres
        int Valide();
};

#endif
