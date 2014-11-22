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

/*
----------------------------------------------------
CRC
----------------------------------------------------
*/
static PROGMEM prog_uint32_t crc_table[16] = {
    0x00000000, 0x1db71064, 0x3b6e20c8, 0x26d930ac,
    0x76dc4190, 0x6b6b51f4, 0x4db26158, 0x5005713c,
    0xedb88320, 0xf00f9344, 0xd6d6a3e8, 0xcb61b38c,
    0x9b64c2b0, 0x86d3d2d4, 0xa00ae278, 0xbdbdf21c
};

unsigned long crc_update(unsigned long crc, byte data)
{
    byte tbl_idx;
    tbl_idx = crc ^ (data >> (0 * 4));
    crc = pgm_read_dword_near(crc_table + (tbl_idx & 0x0f)) ^ (crc >> 4);
    tbl_idx = crc ^ (data >> (1 * 4));
    crc = pgm_read_dword_near(crc_table + (tbl_idx & 0x0f)) ^ (crc >> 4);
    return crc;
}

unsigned long crc32(const char *s)
{
  unsigned long crc = ~0L;
  while (*s)
    crc = crc_update(crc, *s++);
  crc = ~crc;
  return crc;
}

unsigned long crc32l(const char *s, int length)
{
  unsigned long crc = ~0L;
  while (length--)
    crc = crc_update(crc, *s++);
  crc = ~crc;
  return crc;
}

/*
----------------------------------------------------
Equipements
----------------------------------------------------
*/
typedef int (*MessageProc)(unsigned int type, const void* msg, void* data);

typedef struct Object{
	unsigned int name; // crc32
	MessageProc func; // fonction
	void* data; // data
};

typedef struct Command{
	unsigned int name; // crc32
};

typedef struct Config{
	unsigned int name; // crc32
	unsigned int paramName; // crc32
	char paramValue[64]; // crc32
};

typedef struct State{
	unsigned int name; // crc32
	unsigned int paramName; // crc32
};

typedef struct Message{
	union{
          State sta;
          Command cmd;
          Config cfg;
        };
};

// Fonctions
int LedStripObject(unsigned int type, const void* msg, void* data);

typedef struct LedStripData{
	unsigned int FirstPin;
	unsigned int PinCount;
};

LedStripData ledstripData={10,4};

// Table de nommage
static const unsigned int _LedStrip = crc32("ledstrip");
static const unsigned int _CMD      = crc32("CMD");
static const unsigned int _On       = crc32("On");
static const unsigned int _Off      = crc32("Off");
static const unsigned int _Init     = crc32("Init");
static const unsigned int _Periode  = crc32("Periode");

// Table des objets
static const Object object[] = {
	{ _LedStrip, LedStripObject, &ledstripData }
};

// Equipement : LedStrip
int LedStripObject(unsigned int type, const void* _msg, void* _data){
	Message* msg = (Message*)_msg;
	LedStripData* data = (LedStripData*)_data;
	if (type == _CMD){
		if (msg->cmd.name == _On){

		}
		if (msg->cmd.name == _Off){

		}
	}
}

/*
----------------------------------------------------
App
----------------------------------------------------
*/
void setup() {
	// initialise l'equipement
	LedStripObject(_CMD, /*(Command*)*/&_Init, &ledstripData);
	//...
}

void loop() {
	// actualise l'equipement
	LedStripObject(_CMD, /*(Command*)*/&_Periode, &ledstripData);
	//...

    delay(100);
}

