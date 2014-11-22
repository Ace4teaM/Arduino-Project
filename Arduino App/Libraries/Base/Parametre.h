#ifndef parametre_h
#define parametre_h
#include <Arduino.h>
#include <inttypes.h>
#include "CRC32.h"
#include "Evenement.h"

#define PARAM_STRING_MAXLENGTH 64

class Parametre{
public:
	unsigned int id;
	Evenement* changeValeurEvent;
public:
	Parametre();
	Parametre(const char* nom);
	int DefinirValeur(const char* val);
	virtual int LireValeur(const char* val);
};

class ByteParam : public Parametre{
public:
	ByteParam();
	ByteParam(const char* nom, byte val);
	byte valeur;
	virtual int LireValeur(const char* val);
};

class StringParam : public Parametre{
public:
	StringParam();
	StringParam(const char* nom, const char* val);
	char valeur[64];
	virtual int LireValeur(const char* val);
};

class BitParam : public Parametre{
public:
	BitParam();
	BitParam(const char* nom, unsigned char val);
	unsigned char valeur;
	virtual int LireValeur(const char* val);
};

class FloatParam : public Parametre{
public:
	FloatParam();
	FloatParam(const char* nom, float val);
	float valeur;
	virtual int LireValeur(const char* val);
};

class IntParam : public Parametre{
public:
	IntParam();
	IntParam(const char* nom, int val);
	int valeur;
	virtual int LireValeur(const char* val);
};

#endif
