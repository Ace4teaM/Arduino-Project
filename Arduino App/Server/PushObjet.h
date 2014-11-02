#ifndef pushobjet_h
#define pushobjet_h
#include <Arduino.h>
#include <inttypes.h>
#include "Objet.h"

class PushCmd : public Commande{
public:
        // Constructeur
        PushCmd();
        virtual int Executer(Objet* objet);
        virtual int Executable(Objet* objet);
};

class PushObjet : public Objet{
public:
        // Configuration
	ByteParam m_PushPin;
        // Etats
	// ...
        // Commandes
	PushCmd m_PushCmd;
public:
        PushObjet();
        PushObjet(const char* id, byte pushPin);
        virtual int Etats(Parametre** list);
        virtual int Commandes(Commande** list);
        virtual int Configurations(Parametre** list);
        // Evenement periodique
        virtual void Periode();
};


#endif
