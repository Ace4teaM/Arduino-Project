#include "LedStripObject.h"

/*
------------------------------------------
Fonction principale
------------------------------------------
*/

int LedStripObject(unsigned long type, const Message* msg, void* _data){
	LedStripData* data = (LedStripData*)_data;

	//Command
	if (type == _CMD){
		if (msg->cmd.name == _Periode){
			LedStripObject_Periode(data);
		}
		if (msg->cmd.name == _Init){
			LedStripObject_Init(data);
		}
	}

	// Config
	if (type == _CFG){
		LedStripObject_Cfg((Config*)msg, data);
	}
}

/*
------------------------------------------
Methodes
------------------------------------------
*/

// Initialise
void LedStripObject_Init(LedStripData* d){
	//reinitialise les membres
	d->ledValeur = LOW;
	d->curLed = 0;
	d->incLed = 1;

	// d�finit le mode des pins utilis�s
	if (d->FirstPin && d->PinCount)
	for (int i = 0; i<d->PinCount; i++)
		pinMode(d->FirstPin + i, OUTPUT);
}

// Execute 
void LedStripObject_Periode(LedStripData* d){
	if (!d->FirstPin || !d->PinCount)
		return;

	if (d->Mode == LEDSTRIP_MODE_LINEAR){
		for (int i = 0; i<d->PinCount; i++)
			digitalWrite(d->FirstPin + i, d->ledValeur);

		d->ledValeur = (d->ledValeur == HIGH) ? LOW : HIGH;
	}
	if (d->Mode == LEDSTRIP_MODE_DECALE){
		for (int i = 0; i<d->PinCount; i++)
			digitalWrite(d->FirstPin + i, (d->curLed == i) ? HIGH : LOW);

		d->curLed += d->incLed;

		if (d->curLed >= d->PinCount){
			d->incLed = -1;
			d->curLed = d->PinCount - 1;
		}
		if (d->curLed<0){
			d->incLed = 1;
			d->curLed = 0;
		}
	}
}

// Configuration 
void LedStripObject_Cfg(Config* cfg, LedStripData* d){
	int bval;

	// Mode
	if (cfg->name == _Mode){

		if (!sscanf(cfg->value, "%d", &bval))
		{
			Serial.print("Can't read value '");
			Serial.print(cfg->value);
			Serial.println("' for config 'Mode'");
			return;
		}

		if (bval < 0 || bval > 1)
		{
			Serial.println("Invalid value for config 'Mode'");
			return;
		}

		d->Mode = bval;
                Serial.print("Set 'Mode' to ");
                Serial.println(d->Mode,DEC);
	}
        else
            Serial.println("Unknown param name");
}
