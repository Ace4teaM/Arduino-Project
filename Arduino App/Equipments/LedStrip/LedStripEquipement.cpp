#include "LedStripEquipement.h"

	/*
	------------------------------------------
	Methodes
	------------------------------------------
	*/

	// Initialise
	void LedStripEquipement::Initialise(){
            this->InitialiseObjets();
	}

        // Execute 
	void LedStripEquipement::Periode(){
            //actualise les objets
            for(int i=0; i<nObjets; i++)
              this->pObjets[i]->Periode();
            //execute les messages reseau
            MessageTexte message;
            if(this->LireMessageSerie(&message))
              this->LireMessage(&message);
        }

        // Obtient la liste des objets
        int LedStripEquipement::Objets(Objet** list){
            int i=0;
            
            // led switch
            for(int x=0; x<sizeof(led)/sizeof(SwitchObjet); x++)
              list[i++] = &led[x];
            
            // ledstrip
            list[i++] = &strip;
            
            return i;
        }
        
	void LedStripEquipement::InitialiseObjets(){
            Serial.println("Initialize objects...");
            
            this->led[0] = SwitchObjet("led_1",22,0);
            this->led[1] = SwitchObjet("led_2",26,0);
            this->led[2] = SwitchObjet("led_3",30,0);
            this->led[3] = SwitchObjet("led_4",34,0);
            
            this->strip = LedStripObjet("strip",22,4,LEDSTRIP_MODE_DECALE);

            this->nObjets = Objets(this->pObjets);
	}

        // Lit un message sur le port serie
	int LedStripEquipement::LireMessageSerie(MessageTexte* msg){
          return 0;
        }
        // Ecrit un message sur le port serie
	void LedStripEquipement::EcrireMessageSerie(MessageTexte* msg){
        }
        // Execute une commande
	void LedStripEquipement::ExecuterCommande(){
        }
        // Execute une commande
	void LedStripEquipement::ExecuterConfiguration(){
        }

