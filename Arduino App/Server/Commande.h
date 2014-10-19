#ifndef commande_h
#define commande_h
#include <Arduino.h>
#include <inttypes.h>
#include "Message.h"
#include "CRC32.h"

class Commande{
public:
	unsigned int CodeCmd;
	int EquipId;
	int PinNum;
	int Value;

        // liste de codes commandes
        static unsigned int DigitalOut; // DOUT
        static unsigned int DigitalIn;  // DIN
        static unsigned int AnalogOut;  // AOUT
        static unsigned int AnalogIn;   // AIN
        static unsigned int LedHigh;    // LEDH
        static unsigned int LedLow;     // LEDL
public:
        // Constructeur
        Commande();
        // Lit les paramètres d'un message
        int LireParam(MessageTexte* message, char* ofs);
        // Réinitialise les paramètres
        void RaserParam();
        // Vérifie les paramètres
        int Valide();
};

#endif
