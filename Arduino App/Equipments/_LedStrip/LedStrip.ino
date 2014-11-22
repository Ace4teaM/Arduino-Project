/*
---------------------------------------------------------------------------------------------------------------------------------------
(C)2013 Thomas AUGUEY <contact@aceteam.org>
---------------------------------------------------------------------------------------------------------------------------------------
This file is part of Arduino Project (AceTeaM).

This code is free: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This code is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with WebFrameWork.  If not, see <http://www.gnu.org/licenses/>.
---------------------------------------------------------------------------------------------------------------------------------------
*/
/*
#define BEGIN_OBJECT(name) typedef struct name##Data{
#define END_OBJECT         }

#define OBJECT_CMD(name)   static const unsigned int _##name = crc(name)
*/
typedef int(*MessageProc)(unsigned int name, unsigned int type, void* data);

typedef struct Object{
	unsigned int name; // crc32
	MessageProc func; // fonction
	void* data; // data
};

typedef struct Command{
	unsigned int name; // crc32
};

// Fonctions
int LedStripObject(unsigned int name, unsigned int type, void* data);

typedef struct LedStripData{
	unsigned int FirstPin;
	unsigned int PinCount;
}ledstripData, ledstripData1, ledstripData2, ledstripData3, ledstripData4;

// Table de nommage
static const unsigned int _LedStrip = crc("ledstrip");
static const unsigned int _Cmd      = crc("CMD");
static const unsigned int _On       = crc("On");
static const unsigned int _Off      = crc("Off");
static const unsigned int _Init     = crc("Init");
static const unsigned int _Periode  = crc("Periode");

// Table des objets
static const Object[] = {
	{ _LedStrip, LedStripObjet, ledstripData },
	{ _LedStrip1, LedStripObjet1, ledstripData1 },
	{ _LedStrip2, LedStripObjet2, ledstripData2 },
	{ _LedStrip3, LedStripObjet3, ledstripData3 },
	{ _LedStrip4, LedStripObjet4, ledstripData4 }
};

// Equipement : LedStrip
int LedStripObjet(unsigned int type, void* msgData, void* _data){
	Command* cmd = (Command*)msgData;
	LedStripData* data = (LedStripData*)_data;
	if (type == _Cmd){
		if (cmd->name == _On){

		}
		if (cmd->name == _Off){

		}
	}
}

void setup() {
	// initialise l'équipement
	LedStripObjet(_Cmd, (Command*)&_Init);
	//...
}

void loop() {
	// actualise l'équipement
	LedStripObjet(_Cmd, (Command*)&_Periode);
	//...

    delay(100);
}

