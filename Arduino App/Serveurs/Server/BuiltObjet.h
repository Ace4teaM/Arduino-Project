#ifndef builtobjet_h
#define builtobjet_h
#include <Arduino.h>
#include <inttypes.h>
#include <Objet.h>

class BuiltLedOnCmd : public Commande{
public:
	// Constructeur
	BuiltLedOnCmd();
	virtual int Executer(Objet* objet);
	virtual int Executable(Objet* objet);
};

class BuiltLedOffCmd : public Commande{
public:
	// Constructeur
	BuiltLedOffCmd();
	virtual int Executer(Objet* objet);
	virtual int Executable(Objet* objet);
};

class BuiltHelloCmd : public Commande{
public:
	// Constructeur
	BuiltHelloCmd();
	virtual int Executer(Objet* objet);
	virtual int Executable(Objet* objet);
};

class BuiltObjet : public Objet{
public:
	// Configuration
	//...
	// Etats
	//...
	// Commandes
	BuiltLedOnCmd LedOn;
	BuiltLedOffCmd LedOff;
	BuiltHelloCmd Hello;
public:
	BuiltObjet();
	BuiltObjet(const char* id);
	inline virtual unsigned int GetType(){ return crc32("BuiltObjet"); }
	virtual int Etats(Parametre** list);
	virtual int Commandes(Commande** list);
	virtual int Configurations(Parametre** list);
	// Evenement periodique
	virtual void Periode();
};


#endif
