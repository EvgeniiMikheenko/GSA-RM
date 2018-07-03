

#ifndef ST7586S_H

#define	ST7586S_H

#include <stdint.h>
#include <stdbool.h>
#include <fonts.h>



/////////		¬—≈ œ–Œ  ¿–“»Õ »

#define		GPIO_BIT_SET		1
#define		GPIO_BIT_RESET	0

#define		DISP_DATA			1
#define		DISP_COMMAND	0

#define DISP_ON		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_BIT_SET);
#define DISP_OFF	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_BIT_SET);

#define DISP_RESET_ON			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, GPIO_BIT_SET);
#define DISP_RESET_OFF		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, GPIO_BIT_RESET);

#define	DISP_RD_ON				HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, GPIO_BIT_SET);
#define	DISP_RD_OFF				HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, GPIO_BIT_RESET);

#define	DISP_WR_ON				HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_BIT_SET);
#define	DISP_WR_OFF				HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_BIT_RESET);


#define	DISP_A0_ON				HAL_GPIO_WritePin(GPIOA, GPIO_PIN_12, GPIO_BIT_SET);
#define DISP_A0_OFF				HAL_GPIO_WritePin(GPIOA, GPIO_PIN_12, GPIO_BIT_RESET);


#define	DISP_CS_ON				HAL_GPIO_WritePin(GPIOC, GPIO_PIN_8, GPIO_BIT_SET);
#define DISP_CS_OFF				HAL_GPIO_WritePin(GPIOC, GPIO_PIN_8, GPIO_BIT_RESET);



			
#define		DISP_D(a, p)				HAL_GPIO_WritePin(GPIOC, (1 << a), p);			//GPIO_PIN_##a



	



void Disp_Set( void );
void Disp_Init( void );
void Disp_Write( uint8_t pixel );
void Disp_Clr_Port( void );
void Disp_DeInit( void );
void Write( uint8_t type, uint8_t data);
void Disp_Brt( uint16_t brt );



//uint16_t tmp_brt = 0x7fff;


///////////////////////////////// democode

#define USE_DEMO			1



#ifdef 	USE_DEMO

#define MAX_COL		240
#define MAX_ROW		64






void write_dat(unsigned char dat);
void write_cmd(unsigned char cmd);
void Full_on(void);
void Clear(void);
void Horizontal_line(void);
void Vertical_line(void);
void Show_Graph( void );
void TransferData(unsigned long dat);
void LCD_initial(void);
void stp_sc(void);



void put_pixel( uint8_t px, uint8_t py, uint8_t state);
void pic_buf_clr( void );
void st7586s_redraw( void );

void DrawCharOverlay(int x, int y, uint8_t height, 
							  		 const lpFontChar_t fc, 
							  		 uint8_t color,
							  		 int minx, int miny, int maxx, int maxy);
										 
int DrawString( char* str, int len, 
							   int x, int y, 
							   uint8_t color, 
							   lpFontData_t lpFont,
							   int minx, int miny, int maxx, int maxy);
								 /*int DrawString(const char* str, int len, 
							   int x, int y, 
							   uint8_t color, 
							   lpFontData_t lpFont,
							   int minx, int miny, int maxx, int maxy);*/


#endif

/////////////////////////////////	democode



//////////	¬—≈ œ–Œ  ¿–“»Õ »








#endif
