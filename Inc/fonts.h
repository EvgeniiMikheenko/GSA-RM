

#ifndef FONTS_H
#define FONTS_H

#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>

typedef struct FontChar {
	uint16_t Code;
	uint8_t Width;
	// Binary data left to right, top to bottom
	const uint8_t *lpData;
}FontChar_t, *lpFontChar_t;

typedef bool  (*GetCharDataPtr)(char ch, lpFontChar_t *fc);

typedef struct {
	uint8_t height;
	GetCharDataPtr GetCharData;
	uint8_t space;
} FontData_t, *lpFontData_t;


#endif
