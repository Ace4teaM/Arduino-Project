#ifndef message_h
#define message_h
#include <Arduino.h>
#include <inttypes.h>

typedef enum MessageType{
  MessageTypeCommande = 0,
  MessageTypeConfiguration,
  MessageTypeRetourCommande
};

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

	// lit le type de message
	char* LireType(char* ofs, int* type);
        
        // ecrit le type de message
        char* EcrireType(char* ofs, int type);

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
};

#endif
