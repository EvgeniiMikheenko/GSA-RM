
#include "display.h"


//int DrawString( char* str, int len, 
//							   int x, int y, 
//							   uint8_t color, 
//							   lpFontData_t lpFont,
//							   int minx, int miny, int maxx, int maxy)

#define	FRST_LINE		4
#define	SCND_LINE		19
#define	THRD_LINE		34
#define	LAST_LINE		49

const uint16_t divs = 0xFF/3300;


void first_screen( uint8_t frst, uint8_t scnd, uint8_t thrd, uint16_t v_bat)
{
		pic_buf_clr();
			char buf[32];
			int lng = sprintf( buf, "%d %", v_bat );
	
	
		//	DrawString( "Модуль ГСА-Д", 12, 10, FRST_LINE, 1, &Consolas11_Font, 0, 0, 239, 63 );
		//	DrawString( "Модуль 2", 12, SCND_LINE,10, 1, &Consolas11_Font, 0, 0, 239, 63 );
		//	DrawString( "Модуль 3", 12, THRD_LINE,10, 1, &Consolas11_Font, 0, 0, 239, 63 );
	
	
//	len = sprintf( &buf[18], "(%03d.%03d)", x, y ) + 18;
//		//DrawString( buf, strlen(buf), 10,10, 1, &Numbers54x32_Font, 0, 0, 239, 63 );
//		DrawString( buf, len, 10,10, 1, &Consolas11_Font, 0, 0, 239, 63 );
				
//	
			////////////////////////////////////////////////////////////////////////////////////////////////////////
			if( frst == FOUND)
				DrawString( "Модуль ГСА-Д    Обнаружен", 25,  10,FRST_LINE, 1, &Consolas11_Font, 0, 0, 239, 63 );
//			
//			if( scnd == FOUND)
//				DrawString( "Обнаружен", 10, SCND_LINE, 50, 1, &Consolas11_Font, 0, 0, 239, 63 );
//				
//			if( thrd == FOUND)
//				DrawString( "Обнаружен", 10, THRD_LINE, 50, 1, &Consolas11_Font, 0, 0, 239, 63 );
			
			////////////////////////////////////////////////////////////////////////////////////////////////////////

			if( frst == READY)
				DrawString( "Модуль ГСА-Д    Готов", 21, 10, FRST_LINE, 1, &Consolas11_Font, 0, 0, 239, 63 );
			
			
			
			
			
//			if( scnd == READY)
//				DrawString( "Готов", 10, SCND_LINE, 50, 1, &Consolas11_Font, 0, 0, 239, 63 );
//				
//			if( thrd == READY)
//				DrawString( "Готов", 10, THRD_LINE, 50, 1, &Consolas11_Font, 0, 0, 239, 63 );
			
			
			
			DrawString( "Батарея", 		7, 10, LAST_LINE, 1, &Consolas11_Font, 0, 0, 239, 63 );
			DrawString( buf, lng, 70, LAST_LINE,  1, &Consolas11_Font, 0, 0, 239, 63 );	
			DrawString( "%", 1, 100, LAST_LINE,  1, &Consolas11_Font, 0, 0, 239, 63 );		
			
		
			st7586s_redraw();
};




void second_screen( uint16_t temp, uint8_t label, uint16_t pos_val, uint16_t neg_val)
{
		pic_buf_clr();
		char buf[32];
		// sprintf( buf, "%d", value );
		// sprintf( buf, "%d, %d", value1, value2 );
		// sprintf( buf, "%.2f", value );
		// sprintf( buf, "%04X", value );
		switch( label )
		{
			case GSAD:
				
				DrawString( "Модуль ГСА-Д", 12, 10, FRST_LINE, 1, &Consolas11_Font, 0, 0, 239, 63 );
			
			
				DrawString("Значение КНОФ", 13, 10, SCND_LINE,1,&Consolas11_Font, 0, 0, 239, 63 );
				int lng = sprintf( buf, "%d", pos_val/divs );
				DrawString( buf, lng, 150, SCND_LINE, 1, &Consolas11_Font, 0, 0, 239, 63 );
				DrawString("Значение ФОВ", 12, 10, THRD_LINE,1,&Consolas11_Font, 0, 0, 239, 63 );
				lng = sprintf( buf, "%d", neg_val/divs );
				DrawString(	buf, lng, 150, THRD_LINE, 1, &Consolas11_Font, 0, 0, 239, 63 );
			
					

			
			
			break;
			
			case SCND:
				DrawString( "Модуль 2", 8, FRST_LINE,10, 1, &Consolas11_Font, 0, 0, 239, 63 );
				DrawString( "Строка 1", 8, SCND_LINE,10, 1, &Consolas11_Font, 0, 0, 239, 63 );
				DrawString(	"Строка 2", 8, THRD_LINE, 10, 1, &Consolas11_Font, 0, 0, 239, 63 );
			break;
			
			case THRD:
				DrawString( "Модуль 3", 8, FRST_LINE,10, 1, &Consolas11_Font, 0, 0, 239, 63 );
				DrawString( "Строка 1", 8, SCND_LINE,10, 1, &Consolas11_Font, 0, 0, 239, 63 );
				DrawString(	"Строка 2", 8, THRD_LINE, 10, 1, &Consolas11_Font, 0, 0, 239, 63 );
			break;
		};
		
			DrawString( "Температура", 12,10, LAST_LINE,  1, &Consolas11_Font, 0, 0, 239, 63);
			int lng = sprintf( buf, "%.1f", ((float)temp / 100.0f) );	
			DrawString( buf, lng,120, LAST_LINE,  1, &Consolas11_Font, 0, 0, 239, 63);
			st7586s_redraw();


};

void begin_display( void )
{
						pic_buf_clr();
						DrawString( "No connection modules", 21, 10, FRST_LINE, 1, &Consolas11_Font, 0, 0, 239, 63 );
						st7586s_redraw();

};




void last_screen( uint8_t alarm )
{

			pic_buf_clr();
		
		switch(alarm)
		{
			case 0x01 :
				DrawString( "Превышен порог КНОФ", 19,20, SCND_LINE,  1, &Consolas11_Font, 0, 0, 239, 63);
			break;
			case 0x02 :
				DrawString( "Превышен порог ФОВ", 18, 20,SCND_LINE,  1, &Consolas11_Font, 0, 0, 239, 63);
			break;
			case 0x03 :
				DrawString( "Превышен порог опасность КНОФ", 29,20, SCND_LINE,  1, &Consolas11_Font, 0, 0, 239, 63);
			break;
			case 0x04 :
				DrawString( "Превышен порог опасность ФОВ", 28,20, SCND_LINE,  1, &Consolas11_Font, 0, 0, 239, 63);
			break;
		}
	
		DrawString( "ОПАСНО", 6,60, FRST_LINE,  1, &Consolas11_Font, 0, 0, 239, 63);
	
	
		st7586s_redraw();


};
	
