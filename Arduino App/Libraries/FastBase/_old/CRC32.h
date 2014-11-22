#ifndef crc32_h
#define crc32_h

extern unsigned int crc32_tab[];
unsigned int crc32(unsigned int crc, const void *buf, int size);

#endif 