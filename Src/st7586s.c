

#include "st7586s.h"
#include "gpio.h"


unsigned char code_pic[MAX_ROW][MAX_COL/8];

void Disp_Set( void )
{

	DISP_ON;
	DISP_CS_ON;
//	DISP_RD_OFF;
//	DISP_WR_ON;
	DISP_RESET_OFF;
	
};


void Disp_Init( void )
{
//	DISP_ON;
//	DISP_CS_ON;
////	DISP_RD_OFF;
////	DISP_WR_ON;
//	DISP_RESET_OFF;
	
	HAL_Delay( 0x78 );
	Write(DISP_COMMAND, 0xD7);
	Write(DISP_DATA, 0x9F);
	Write(DISP_COMMAND, 0xE0);
	Write(DISP_DATA, 0x00); 
	HAL_Delay(0xA); 
	Write(DISP_COMMAND, 0xE3); 
	HAL_Delay(0x14); 
	Write(DISP_COMMAND, 0xE1); 
	Write(DISP_COMMAND, 0x11); 
	Write(DISP_COMMAND, 0x28); 
	HAL_Delay(0x32); 
	Write(DISP_COMMAND, 0xC0); 
	Write(DISP_DATA, 0xB9); 
	Write(DISP_DATA, 0x00); 
	Write(DISP_COMMAND, 0xC3); 
	Write(DISP_DATA, 0x05); 
	Write(DISP_COMMAND, 0xC4); 
	Write(DISP_DATA, 0x07); 
	Write(DISP_COMMAND, 0xD0); 
	Write(DISP_DATA, 0x1D); 
	Write(DISP_COMMAND, 0xB5); 
	Write(DISP_DATA, 0x00); 
	Write(DISP_COMMAND, 0x39); 
	Write(DISP_COMMAND, 0x3A); 
	Write(DISP_DATA, 0x02); 
	Write(DISP_COMMAND, 0x36); 
	Write(DISP_DATA, 0x00); 
	Write(DISP_COMMAND, 0xB0); 
	Write(DISP_DATA, 0x9F); 
	Write(DISP_COMMAND, 0xB4); 
	Write(DISP_DATA, 0xA0); 
	Write(DISP_COMMAND, 0x30); 
	Write(DISP_DATA, 0x00); 
	Write(DISP_DATA, 0x00); 
	Write(DISP_DATA, 0x00); 
	Write(DISP_DATA, 0x77); 
	Write(DISP_COMMAND, 0x20);
	Write(DISP_COMMAND, 0x2A); 
	Write(DISP_DATA, 0x00); 
	Write(DISP_DATA, 0x00); 
	Write(DISP_DATA, 0x00); 
	Write(DISP_DATA, 0x7F);
	
	
	
	Write(DISP_COMMAND, 0x2B);
	Write(DISP_DATA, 0x00);
	Write(DISP_DATA, 0x00);
	Write(DISP_DATA, 0x00);
	Write(DISP_DATA, 0x9F);
	Write(DISP_COMMAND, 0x2A);
	Write(DISP_DATA, 0x00);
	Write(DISP_DATA, 0x00);
	Write(DISP_DATA, 0x00);
	Write(DISP_DATA, 0x4F);
	Write(DISP_COMMAND, 0x2B);
	Write(DISP_DATA, 0x00);
	Write(DISP_DATA, 0x00);
	Write(DISP_DATA, 0x00);
	Write(DISP_DATA, 0x78);
	Write(DISP_COMMAND, 0x29);

	
	
	
	
	
	
		
	
	

};

void Disp_Clr_Port( void )
{
		GPIOC->BSRR |= 0xFF0000;	
};

void Disp_Write( uint8_t pixel )
{

	Disp_Clr_Port();
	for( int i = 0; i < 8; i++)
	{
	
		if( pixel & (1 << i) )
			DISP_D(i, GPIO_BIT_SET);
		
		if(  i == 7 )
		{
			uint8_t dsfdsf = 0;
		};
		
	
	};
	
};
	

void Disp_DeInit( void )
{

	DISP_RESET_ON;
	DISP_CS_OFF;
	

};



void Write( uint8_t type, uint8_t data)
{

		if( type == DISP_DATA )
		{
			DISP_A0_ON;
		}
		else if( type == DISP_COMMAND )
		{
			DISP_A0_OFF;
		}
		
		Disp_Write( data );
};
		
void Disp_Brt( uint16_t brt )
{			 
		TIM3->CCR4 = brt;
};
	





/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


#ifdef  USE_DEMO



void write_dat(unsigned char dat)
{
		DISP_RD_ON;
		DISP_WR_OFF;
		DISP_CS_OFF;
		DISP_A0_ON;
		
		Disp_Write(dat);
		
		DISP_CS_OFF;
		DISP_WR_ON;
		__nop();
    DISP_A0_ON;
    DISP_CS_ON;	
};



void write_cmd(unsigned char cmd)
{
	DISP_RD_ON;
	DISP_WR_OFF;
  DISP_A0_OFF;
  Disp_Write( cmd );  
  DISP_CS_OFF;
	DISP_WR_ON;
	__nop();
	DISP_A0_ON; 		
	DISP_CS_ON;			
};

void Full_on(void)
{
	unsigned char i=0,j=0;

	write_cmd(0x2c);//write display data
	for (i=0;i<MAX_ROW;i++)
	{
		for (j=0;j<MAX_COL/3;j++)
			write_dat(0x00);
	}
};



void Clear(void)
{
	unsigned char i=0,j=0;

	write_cmd(0x2c);//write display data
	for (i=0;i<MAX_ROW;i++)
	{
		for (j=0;j<MAX_COL/3;j++)
			write_dat(0x00);
	}
};

void Horizontal_line(void)
{
	unsigned char i=0,j=0;

	write_cmd(0x2c);//write display data
	for (i=0;i<MAX_ROW/2;i++)
	{
		for (j=0;j<MAX_COL/3;j++)
			write_dat(0xff);
		for (j=0;j<MAX_COL/3;j++)
			write_dat(0x00);
	}
}



void Vertical_line(void)
{
	unsigned char i=0,j=0;

	write_cmd(0x2c);//write display data
	for (i=0;i<MAX_ROW;i++)
	{
		for (j=0;j<MAX_COL/6;j++)
		{
			write_dat(0xc3);
			write_dat(0x18);
		}
	}
}




void Show_Graph( void )
{
	unsigned char i=0,j=0,cnt=0;
	unsigned long tmp=0;

	write_cmd(0x2c);//write display data
	for (i=0;i<MAX_ROW;i++)
	{
		for (j=0;j<MAX_COL/8;j++)
		{
			tmp=code_pic[i][j]|tmp;
			tmp<<=8;
			cnt++;
			if (cnt==3)
			{
				TransferData(tmp);
				cnt=0;
				tmp=0;
			}
		}
	}
}


void Show_Line( unsigned char arr[] )
{
		uint8_t i = 0, j = 0, cnt = 0;
	
	
		write_cmd(0x2c);
		for(i = 0; i<64; i++)
		{
				
		}
};


void TransferData(unsigned long dat)
{
	unsigned char i=0,cnt=0,tmp1=0,tmp2=0;
	unsigned long tmp=0,tmp3=0x80000000;

	tmp=dat;

	for (i=0;i<24;i++)
	{
		if (tmp&tmp3)
			tmp1=0x03;
		else
			tmp1=0x00;
		tmp2=tmp1|tmp2;
		if (cnt<2)
			tmp2<<=3;
		cnt++;
		if (cnt==3)
		{
			write_dat(tmp2);
			cnt=0;
			tmp2=0;
		}
		tmp<<=1;	
	}
}

void put_pixel( uint8_t px, uint8_t py, uint8_t state)
{

		if( px > 0xF0 ||	py > 0x3C)
			return;
		
		px = MAX_COL - px - 1;
		py = MAX_ROW - py - 1;
		
		
		uint8_t col_num = px / 8;
		uint8_t x_shift = 7 - (px % 8);
 		if( state )
			code_pic[py][col_num] |= (1 << x_shift);
		else
			code_pic[py][col_num] &= ~(1 << x_shift);
};


void pic_buf_clr( void )
{
	for(uint16_t i = 0; i < 0x780; i++)
		code_pic[i / 30][i % 30] = 0;
};







int DrawString( char* str, int len, 
							   int x, int y, 
							   uint8_t color, 
							   lpFontData_t lpFont,
							   int minx, int miny, int maxx, int maxy)					//int DrawString(const char* str, int len, int x, int y, uint8_t color,lpFontData_t lpFont, int minx, int miny, int maxx, int maxy)
{
	int dispW = MAX_COL;
	int dispH = MAX_ROW;
	
	if((str == NULL) || (lpFont == NULL) || (x >= dispW) || (y >=dispH))
		return 0;
	//
	lpFontChar_t fc = (lpFontChar_t)NULL;
	//
	uint8_t h = (uint8_t)lpFont->height;
	int startX = x;
	int w = 0;
	for( int i = 0; i < len; i++ ) {
		lpFont->GetCharData( str[i], &fc );
		if( fc == NULL )
			continue;
		//
		DrawCharOverlay( x, y, h, fc, color, minx, miny, maxx, maxy );
		//
		w = (fc->Width + lpFont->space);
		x += w;
		if( x >= dispW )
			break;
	}
	return x - startX;
}





void DrawCharOverlay(int x, int y, uint8_t height, 
							  		 const lpFontChar_t fc, 
							  		 uint8_t color,
							  		 int minx, int miny, int maxx, int maxy) {
	if( x >= MAX_COL )
		return;
	
	if( y >= MAX_ROW )
		return;
	
	if(fc == NULL)
		return;
	//
	int w = fc->Width;
	uint8_t data;
	uint8_t mask = 0x00;
	int index = 0;
	int px, py;
	//
	for(int row = 0; row < height; row++) {
		if(mask == 0) {
			data = fc->lpData[index++];
			mask = 0x01;
		}
		
		for(int col = 0; col < w; col++) {
			//
			px = col + x;
			py = row + y;
			if((px >= minx) && (px <= maxx) && (py >= miny) && (py <= maxy)) {
				if(data & mask) {
						put_pixel( px, py, color );
				}
			}
			//
			mask <<= 1;
			if(mask == 0) {
				data = fc->lpData[index++];
				mask = 0x01;
			}
		}
	}
}


void LCD_initial(void)
{
	DISP_RESET_ON;		//LCM_RESET=1;
  HAL_Delay(0x78);	// 	Delay_ms(120);
  DISP_RESET_OFF; 	//LCM_RESET=0;
  HAL_Delay(0xA);  	//Delay_ms(10);
  DISP_RESET_ON;  		//LCM_RESET=1;
  HAL_Delay(0x78);		//	Delay_ms(120);

    write_cmd(0xD7);		// Disable Auto Read
	write_dat(0x9F);
			
	write_cmd(0xE0);		// Enable OTP Read
	write_dat(0x00);		
	HAL_Delay(0xA);			//Delay_ms(10);
		
	write_cmd(0xE3);		// OTP Up-Load
	HAL_Delay(0x14);			//Delay_ms(20);
		
	write_cmd(0xE1);		// OTP Control Out

	write_cmd(0x11);		// Sleep Out

	write_cmd(0x28);		// Display OFF
	HAL_Delay(0x32);			//Delay_ms(50);	
		
	write_cmd(0xC0);		// Set Vop
	write_dat(0x9E);		// difference	democode(0x9E) vs datasheet(0xB9)
	write_dat(0x00);		// 

	write_cmd(0xC3);		// BIAS System
	write_dat(0x05);		// 

	write_cmd(0xC4);		// Booster Level
	write_dat(0x05);		
	
	write_cmd(0xD0);		// Enable Analog Circuit
	write_dat(0x1D);
			
	write_cmd(0xB5);		// N-Line Inversion
	write_dat(0x00);		//

	write_cmd(0x39);		// Display Mode

	write_cmd(0xF1);		// Frame Rate (Monochrome Mode) 
	write_dat(0x06);		// 
	write_dat(0x0B);		// 
	write_dat(0x0D);		//	
	write_dat(0x10);		//

	write_cmd(0x3A);		// Enable DDRAM Interface
	write_dat(0x02);

    	write_cmd(0x36);		// Display Control
	write_dat(0xC8);		//				(0xC8)
                           
	write_cmd(0xB0);		// Display Duty
	write_dat(0x3F);		//
	
	write_cmd(0x20);		// Inverse Display

	write_cmd(0x37);		// Start Line
	write_dat(0x00);		//

	write_cmd(0xB1);		// First Output COM
	write_dat(0x00);		//

	write_cmd(0xB3);		// FOSC Divider
	write_dat(0x01);

	write_cmd(0x2A);		// Set Column Address
	write_dat(0x00);		// 
	write_dat(48);          	//		
	write_dat(0x00);		//
	write_dat(127);		    	//
			
	write_cmd(0x2B);		// Set Row Address
	write_dat(0x00);		// 
	write_dat(96);		    	//
	write_dat(0x00);		//	
	write_dat(159);		    	//
	
	write_cmd(0xC4);		// Booster Level
	write_dat(0x07);



	//write_cmd(0x22);
	write_cmd(0x29);		// Display ON
	
	
}


//unsigned char code_pic[MAX_ROW][MAX_COL/8];


void st7586s_redraw( void )
{
	
//
	Show_Graph();
	
	

};

#endif

