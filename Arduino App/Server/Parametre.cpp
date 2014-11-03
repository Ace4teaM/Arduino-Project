#include "Parametre.h"

// Constructeur
Parametre::Parametre(){
  this->id = 0;
  this->changeValeurEvent = 0;
}
Parametre::Parametre(const char* nom){
  this->id = crc32(0,nom,strlen(nom));
  this->changeValeurEvent = 0;
}

int Parametre::LireValeur(const char* val){
  return 0;
}

// Definit la valeur du paramètre
int Parametre::DefinirValeur(const char* val){
    int r = this->LireValeur(val);

    if(!r){
      Serial.print("Invalid Value:");
      Serial.println(val);
      return 0;
    }
    
    if(this->changeValeurEvent != 0)
       this->changeValeurEvent->Executer();
       
    return r;
}

// Constructeur
ByteParam::ByteParam() : Parametre(){}
ByteParam::ByteParam(const char* nom, byte val) : Parametre(nom){
  this->valeur = val;
}
        
// Lit la valeur du paramètre
int ByteParam::LireValeur(const char* val){
    int i=0;
    if(!sscanf(val,"%d",&i))
      return 0;
    if(i<0||i>255)
      return 0;
    this->valeur = (byte)i;
    return 1;
}

// Constructeur
StringParam::StringParam() : Parametre(){}
StringParam::StringParam(const char* nom, const char* val) : Parametre(nom){
    if(strlen(val)<PARAM_STRING_MAXLENGTH)
      strcpy(this->valeur,val);
}

// Lit la valeur du paramètre
int StringParam::LireValeur(const char* val){
    if(strlen(val)>PARAM_STRING_MAXLENGTH)
      return 0;
    strcpy(this->valeur,val);
    return 1;
}

// Constructeur
BitParam::BitParam() : Parametre(){}
BitParam::BitParam(const char* nom, unsigned char val) : Parametre(nom){
  this->valeur = val;
}

// Lit la valeur du paramètre
int BitParam::LireValeur(const char* val){
  if(val[0] == '1')
    this->valeur = 1;
  else if(val[0] == '0')
    this->valeur = 0;
  else return 0;
 return 1;
}

// Constructeur
FloatParam::FloatParam() : Parametre(){}
FloatParam::FloatParam(const char* nom, float val) : Parametre(nom){
  this->valeur = val;
}

// Lit la valeur du paramètre
int FloatParam::LireValeur(const char* val){
    return sscanf(val,"%f",&this->valeur);
}

// Constructeur
IntParam::IntParam() : Parametre(){}
IntParam::IntParam(const char* nom, int val) : Parametre(nom){
  this->valeur = val;
}

// Lit la valeur du paramètre
int IntParam::LireValeur(const char* val){
    return sscanf(val,"%d",&this->valeur);
}

