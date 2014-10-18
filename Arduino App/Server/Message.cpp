#include "Message.h"

const char MessageTexte::endOfParamName = '=';
const char MessageTexte::endOfParamValue = ';';

//constructeur
MessageTexte::MessageTexte(){
  this->buf = NULL;
  this->endOfBuf = NULL;
}

MessageTexte::MessageTexte(char * buf, int sizeOfBuf){
  this->buf = buf;
  this->endOfBuf = buf + sizeOfBuf;
}

// obtient l'offset de base
char* MessageTexte::GetBuffer(){
  return this->buf;
}

// vérifie la structure du message
int MessageTexte::Verifier(){
        if(this->LireSignature(this->buf) == 0)
          return 0;
	return 1;
}

// lit le type de message
char* MessageTexte::LireType(char* ofs, int* type){
	if (ofs < buf || ofs + 3 > endOfBuf)
		return 0;

	if (ofs[0] == 'C' && ofs[1] == 'M' && ofs[2] == 'D'){
                *type = MessageTypeCommande;
		return ofs + 3;
        }
        
	if (ofs[0] == 'C' && ofs[1] == 'F' && ofs[2] == 'G'){
                *type = MessageTypeConfiguration;
		return ofs + 3;
        }
        
        return 0;
}

// ecrit la signature
char* MessageTexte::EcrireSignature(char* ofs){
	if (ofs < buf || ofs + 3 > endOfBuf)
		return 0;
	//lit la signature
	*ofs++ = 'M';
	*ofs++ = 'S';
	*ofs++ = 'G';
	return ofs;
}

// lit la signature
char* MessageTexte::LireSignature(char* ofs){
	if (ofs < buf || ofs > endOfBuf)
		return 0;
	//lit la signature
	if (ofs[0] == 'M' && ofs[1] == 'S' && ofs[2] == 'G')
		return ofs + 3;
	return 0;
}

// ecrit la signature
char* MessageTexte::EcrireParam(char* ofs, const char* nom, const char* valeur){
	int nomSize = strlen(nom);
	int valeurSize = strlen(valeur);

	if (ofs < buf || ofs > endOfBuf)
		return 0;

	if (nomSize < 1 || valeurSize < 1 || ofs + (nomSize + valeurSize + 2) >= endOfBuf)
		return 0;

	//ecrit les données
	memcpy(ofs, nom, nomSize);
	ofs += nomSize;

	*ofs++ = this->endOfParamName;

	memcpy(ofs, valeur, valeurSize);
	ofs += valeurSize;

	*ofs++ = this->endOfParamValue;

	return ofs;
}

// lit un parametre
char* MessageTexte::LireParam(char* ofs, char* nom, char* valeur){

	if (ofs < buf || ofs > endOfBuf)
		return 0;

	//lit le nom
	while (ofs < endOfBuf && *ofs != this->endOfParamName){
		*(nom++) = *(ofs++);
	}
	*nom = '\0';
	*ofs++;

	//lit la valeur
	while (ofs < endOfBuf && *ofs != this->endOfParamValue){
		*(valeur++) = *(ofs++);
	}
	*valeur = '\0';
	*ofs++;

	return ofs;
}
