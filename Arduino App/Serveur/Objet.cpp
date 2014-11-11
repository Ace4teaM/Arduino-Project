#include "Objet.h"

// Constructeur
Objet::Objet(){
	this->id = 0;
}

Objet::Objet(const char* id){
	this->id = crc32(0, id, strlen(id));
}

// Obtient une commande par son identifiant
Commande* Objet::GetCommande(unsigned int Id){
	Commande* list[OBJET_MAX_CMD];
	int maxCmd = Commandes(list);
	for (int x = 0; x<maxCmd; x++){
		if (list[x]->id == Id)
			return list[x];
	}
	return 0;
}

// Obtient un parametre de configuration par son identifiant
Parametre* Objet::GetConfiguration(unsigned int Id){
	Parametre* list[OBJET_MAX_CFG];
	int maxCfg = Configurations(list);
	for (int x = 0; x<maxCfg; x++){
		if (list[x]->id == Id)
			return list[x];
	}
	return 0;
}

// Execute une commande
// "[CmdId];"
int Objet::ExecuterCommande(MessageTexte* message, char* ofs /*, MessageTexte* responseMessage, char* responseOfs*/){
	Commande *cmd = 0;
	unsigned int id = 0;

	Serial.println("Read command");
	if (0 == (ofs = message->LireStrCrc(ofs, ';', &id))){
		Serial.println("Command not specified");
		return 0;
	}
	// obtient puis execute la commande
	cmd = this->GetCommande(id);
	if (cmd != 0 && cmd->Executable(this))
		return cmd->Executer(this);

	Serial.println("Command not found");
	return 0;
}

// Execute une configuration
// "[ConfigId]=[Valeur];"
int Objet::ExecuterConfiguration(MessageTexte* message, char* ofs /*, MessageTexte* responseMessage, char* responseOfs*/)
{
	Parametre *cfg = 0;
	unsigned int id = 0;
	char valeur[MESSAGE_MAX_STRING];

	// Obtient l'identifiant de la config
	if (0 == (ofs = message->LireStrCrc(ofs, '=', &id))){
		Serial.println("Config not specified");
		return 0;
	}

	// obtient puis execute la commande
	cfg = this->GetConfiguration(id);
	if (cfg != 0 && 0 != (ofs = message->LireTexte(ofs, ';', valeur))){
		return cfg->DefinirValeur(valeur);
	}

	Serial.println("Value not specified");
	return 0;
}

// Execute une configuration
int Objet::ExecuterEtat(MessageTexte* message, char* ofs /*, MessageTexte* responseMessage, char* responseOfs*/)
{
	Serial.println("Not suported");
	return 0;
}
