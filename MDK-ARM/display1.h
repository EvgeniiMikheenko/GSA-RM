


#ifndef DISPLAY_H
#define DISPLAY_H

#include <stdint.h>
#include "Consolas11.h"
#include <st7586s.h>


#define FOUND			0x01
#define	READY			0x02


#define	GSAD			0x11
#define	SCND			0x12
#define	THRD			0x13

void first_screen( uint8_t frst, uint8_t scnd, uint8_t thrd, uint16_t v_bat);

void second_screen( uint16_t temp, uint8_t label, uint16_t pos_val, uint16_t neg_val);



void last_screen( uint8_t alarm );






#endif 				/// DISPLAY_H