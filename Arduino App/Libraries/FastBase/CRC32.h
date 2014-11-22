#ifndef crc32_h
#define crc32_h

#ifdef __cplusplus
extern "C" {
#endif

	extern unsigned long crc32(const char *s);
	extern unsigned long crc32l(const char *s, int length);

#ifdef  __cplusplus
}
#endif

#endif 