


#include "button.h"
#include <stdint.h>





void Tick( void )
{

	
	
	

	uint32_t adcstat;
			
			
	Vbat_Filter( HAL_ADC_GetValue( &hadc1) );
	
	
	adcstat = HAL_ADC_Start( &hadc1 );
	
	
	if(tickcounter % 100 == 0)
	{
		button1 = button1 << 1;
	
		if( !Check_Button1() )
			button1 |= 1;
		
		if( tickcounter % 200 == 0)
		{
			
			
			BEEP_ON;
		}
		else
		{
			BEEP_OFF;
		}
		

		
		
	}
	
	
	if( button1 == 0xFF && button1_state == OFF)
	{
	//	GSA_ON;
		button1_state = ON;
		button1 = 0;
		
	};
	
	
	if(	button1 == 0xFF && button1_state == ON)
	{
	//	GSA_OFF;
		button1_state = OFF;
		button1= 0;
	}
	
};