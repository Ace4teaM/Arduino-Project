#ifndef ledstripobjet_h
#define ledstripobjet_h
#include <Arduino.h>
#include <inttypes.h>
#include "Objet.h"

#define LEDSTRIP_MODE_LINEAR 0
#define LEDSTRIP_MODE_DECALE 1

class AnimationModeParam : public ByteParam{
public:
	inline AnimationModeParam() : ByteParam(){}
	inline AnimationModeParam(const char* nom, byte val) : ByteParam(nom, val){}
	virtual int LireValeur(const char* val);
};

class LedStripObjet : public Objet{
public:
	// Configuration
	ByteParam FirstPin; // preminer numéro de pin
	ByteParam PinCount; // dernier numéro de pin
	AnimationModeParam AnimationMode; // mode d'animation: 0=linéaire, 1=décalé
	Evenement* changeEvent;

	// membres
	int ledValeur;
	int curLed, incLed;
public:
	LedStripObjet();
	LedStripObjet(const char* id);
	LedStripObjet(const char* id, byte firstPin, byte pinCount, byte mode);
	virtual int Etats(Parametre** list);
	virtual int Commandes(Commande** list);
	virtual int Configurations(Parametre** list);
	// Evenement periodique
	virtual void Periode();
};

class LedStripPinChangeEvent : public Evenement{
public:
	LedStripObjet* obj;
	LedStripPinChangeEvent();
	LedStripPinChangeEvent(LedStripObjet* ptr);
	virtual int Executer();
};

#endif
