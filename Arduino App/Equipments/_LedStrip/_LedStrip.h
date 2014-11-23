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
#ifndef LedStrip_h
#define LedStrip_h
#include <Arduino.h>
#include <inttypes.h>
/*
#define BEGIN_OBJECT(name) typedef struct name##Data{
#define END_OBJECT         }

#define OBJECT_CMD(name)   static const unsigned long _##name = crc(name)
*/

/*
----------------------------------------------------
CRC
----------------------------------------------------
*/
unsigned long crc_update(unsigned long crc, byte data);
unsigned long crc32(const char *s);
unsigned long crc32l(const char *s, int length);

/*
----------------------------------------------------
Buffer
----------------------------------------------------
*/
const char* ReadCrc(const char *buf, const char * bufEnd, char lastChar, unsigned long* crc);
const char* ReadCrcLen(const char *buf, const char * bufEnd, int length, unsigned long* crc);
const char* ReadStr(const char *buf, const char * bufEnd, char separator, char * dst, unsigned int dstLength);

/*
----------------------------------------------------
Equipements
----------------------------------------------------
*/
typedef struct Command{
	unsigned long name; // crc32
};

typedef struct Config{
	unsigned long name; // crc32
	char value[64]; // crc32
};

typedef struct State{
	unsigned long name; // crc32
	unsigned long paramName; // crc32
};

typedef struct Message{
	union{
		State sta;
		Command cmd;
		Config cfg;
	};
};

typedef int(*MessageProc)(unsigned long type, const Message* msg, void* data);

typedef struct Object{
	unsigned long name; // crc32
	MessageProc func; // fonction
	void* data; // data
};

/*
----------------------------------------------------
Fonctions
----------------------------------------------------
*/

#define SERIAL_BUFFER_MAX_SIZE 128
#define SERIAL_AND_OF_STRING_CHAR '$'

unsigned long ParseMessage(Message* msg);

/*
----------------------------------------------------
Table de nommage
----------------------------------------------------
*/

static const unsigned long _CMD = crc32("CMD");
static const unsigned long _CFG = crc32("CFG");
static const unsigned long _STA = crc32("STA");
static const unsigned long _Init = crc32("Init");
static const unsigned long _Periode = crc32("Periode");

#endif
