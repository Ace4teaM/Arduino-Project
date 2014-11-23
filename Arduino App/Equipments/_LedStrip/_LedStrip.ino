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

#include <Arduino.h>
#include <inttypes.h>
#include "_LedStrip.h"
#include "LedStripObject.h"
#include "MemoryFree.h"

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
Buffer
----------------------------------------------------
*/
const char* ReadCrc(const char *buf, const char * bufEnd, char lastChar, unsigned long* _crc){
	unsigned long crc = ~0L;
	while (buf < bufEnd && *buf != lastChar)
		crc = crc_update(crc, *buf++);
	crc = ~crc;
        *_crc = crc;
	buf++;
	return buf;
}

const char* ReadCrcLen(const char *buf, const char * bufEnd, int length, unsigned long* crc){
	*crc = 0;
	if (buf + length > bufEnd)
		return 0;
	*crc = crc32l(buf, length);
	return buf + length;
}

const char* ReadStr(const char *buf, const char * bufEnd, char separator, char * dst, unsigned int dstLength)
{
	char* dstEnd = dst + dstLength - 1;

	//lit le nom
	while (buf < bufEnd && dst < dstEnd && *buf != separator){
		*(dst++) = *(buf++);
	}
	*dst = '\0';
	buf++;

	return buf;
}

/*
----------------------------------------------------
Fonctions
----------------------------------------------------
*/

unsigned long ParseMessage(unsigned long* objectId, Message* msg){
	unsigned long type = 0;
	unsigned long equipId = 0;
	int packetSize = 0;
	char serialBuffer[SERIAL_BUFFER_MAX_SIZE];
	const char* ofs = serialBuffer;
	const char* bufEnd = serialBuffer + SERIAL_BUFFER_MAX_SIZE;
	*objectId = 0;

	// Lit les données du port série
	if (Serial.available()){
		packetSize = Serial.readBytesUntil(SERIAL_AND_OF_STRING_CHAR, serialBuffer, SERIAL_BUFFER_MAX_SIZE - 1);
		serialBuffer[packetSize] = 0;
	}

	// pas de message ?
	if (!packetSize)
		return 0;

	// infos
	Serial.print("Received packet of size ");
	Serial.println(packetSize, DEC);
	Serial.print("Data = ");
	Serial.println(serialBuffer);

	// lit le message
	ofs = ReadCrc(ofs, bufEnd, ';', &type);
	ofs = ReadCrc(ofs, bufEnd, ';', &equipId);
	ofs = ReadCrc(ofs, bufEnd, ';', objectId);

	Serial.print("type = 0x");
	Serial.println(type, HEX);
	Serial.print("equipId = 0x");
	Serial.println(equipId, HEX);
	Serial.print("objectId = 0x");
	Serial.println(*objectId, HEX);

	if (type == _CMD){
		Serial.println("type = _CMD");
		ofs = ReadCrc(ofs, bufEnd, ';', &msg->cmd.name);
	}
	else if (type == _CFG){
		Serial.println("type = _CFG");
		ofs = ReadCrc(ofs, bufEnd, '=', &msg->cfg.name);
		ofs = ReadStr(ofs, bufEnd, ';', msg->cfg.value, sizeof(msg->cfg.value));
	}
	else if (type == _STA){
		Serial.println("type = _STA");
		ofs = ReadCrc(ofs, bufEnd, ';', &msg->sta.name);
		ofs = ReadCrc(ofs, bufEnd, ';', &msg->sta.paramName);
	}
	return type;
}


/*
----------------------------------------------------
Equipements
----------------------------------------------------
*/
LedStripData ledstripData = { 2, 5, LEDSTRIP_MODE_LINEAR };

// Table des objets
static const Object object[] = {
	{ crc32("ledstrip"), LedStripObject, &ledstripData }
};

/*
----------------------------------------------------
App
----------------------------------------------------
*/
void setup() {
	// Open serial communications and wait for port to open:
	Serial.begin(9600);
	while (!Serial) {
		; // wait for serial port to connect. Needed for Leonardo only
	}
	Serial.println("Start");

	// initialise les objets
	for (int i = 0; i<(sizeof(object) / sizeof(Object)); i++)
		object[i].func(_CMD, (const Message*)&_Init, object[i].data);
	//...

	Serial.print("FreeMemory=");
	Serial.print(freeMemory(), DEC);
	Serial.println(" bytes");
}

void loop() {
	const Object * pobj = object;
	const Object * pobjEnd = object + (sizeof(object) / sizeof(Object));
	Message msg;
	unsigned long type = 0;
	unsigned long objectId = 0;

	// traite le message
	type = ParseMessage(&objectId, &msg);
	if (type != 0){
		while (pobj < pobjEnd && pobj->name != objectId)
			pobj++;

		if (pobj < pobjEnd && pobj->name == objectId)
			pobj->func(type, (const Message*)&msg, pobj->data);
                else
                  Serial.println("Object not found");
	}

	// actualise les objets
	for (int i = 0; i<(sizeof(object) / sizeof(Object)); i++)
		object[i].func(_CMD, (const Message*)&_Periode, object[i].data);

	delay(100);
}

