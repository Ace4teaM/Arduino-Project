#ifndef message_h
#define message_h
#include <Arduino.h>
#include <inttypes.h>
#include "CRC32.h"

#define MESSAGE_MAX_STRING 128

static const unsigned int MessageTypeCommande = crc32(0, "CMD", 3);
static const unsigned int MessageTypeConfiguration = crc32(0, "CFG", 3);
static const unsigned int MessageTypeEtat = crc32(0, "ETA", 3);

typedef struct _MESSAGE_ENTETE{
	char Signature[3];
	char Type[3];
	char CodeEquip[6];
	char CodeObjet[6];
}MESSAGE_ENTETE;

class MessageTexte{
private:
	char * buf;
	char * endOfBuf;
	int length;
	static const char endOfParamName;
	static const char endOfParamValue;
public:
	MessageTexte();
	MessageTexte(char * buf, int sizeOfBuf);

	// obtient l'offset de base
	char* GetBuffer();

	// vérifie la structure du message
	int Verifier();

	// lit le crc d'un texte
	char* LireCrc(char* ofs, int length, unsigned int* crc);

	// lit le crc d'un texte
	char* LireStrCrc(char* ofs, char separator, unsigned int* crc);

	// lit le type de message
	char* LireType(char* ofs, unsigned int* type);

	// ecrit le type de message
	char* EcrireType(char* ofs, unsigned int type);

	// ecrit la signature
	char* EcrireSignature(char* ofs);

	// lit la signature
	char* LireSignature(char* ofs);

	// ecrit la signature
	char* EcrireParam(char* ofs, const char* nom, const char* valeur);

	// ecrit la signature
	char* EcrireParam(char* ofs, const char* nom, int valeur);

	// lit un parametre
	char* LireParam(char* ofs, char* nom, char* valeur);

	// lit un texte
	char* LireTexte(char* ofs, char separator, char* texte);

};

#endif
