#ifndef LedStripObject_h
#define LedStripObject_h
#include <Arduino.h>
#include <inttypes.h>
#include "_LedStrip.h"

/*
----------------------------------------------------
LedStrip
----------------------------------------------------
*/

#define LEDSTRIP_MODE_LINEAR 0
#define LEDSTRIP_MODE_DECALE 1


// Fonctions
int LedStripObject(unsigned long type, const Message* msg, void* data);

typedef struct LedStripData{
	// cfg
	byte FirstPin;
	byte PinCount;
	byte Mode;
	// etats
	int ledValeur;
	int curLed;
	int incLed;
};

void LedStripObject_Init(LedStripData* d);
void LedStripObject_Periode(LedStripData* d);
void LedStripObject_Cfg(Config* cfg, LedStripData* d);

/*
----------------------------------------------------
Table de nommage
----------------------------------------------------
*/

static const unsigned long _Mode = crc32("Mode");

#endif
