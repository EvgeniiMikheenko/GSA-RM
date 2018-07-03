/**
  ******************************************************************************
  * File Name          : main.c
  * Description        : Main program body
  ******************************************************************************
  *
  * COPYRIGHT(c) 2016 STMicroelectronics
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */
/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx_hal.h"
#include "adc.h"
#include "spi.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"
#include "stm32f1xx_it.h"
#include <st7586s.h>
#include "Numbers54x32.h"
#include "Consolas11.h"
#include "modbs_master.h"
#include "GSAD.h"
#include "display.h"
//#include "iwdg.h"


#include <stdbool.h>



#define GSA_ON		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_9, GPIO_BIT_SET);				//GPIO_BIT_SET
#define GSA_OFF		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_9, GPIO_BIT_RESET);				//GPIO_BIT_RESET

#define PCD_ON		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_8, GPIO_BIT_SET);
#define PCD_OFF		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_8, GPIO_BIT_RESET);


#define BEEP_ON		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_7, GPIO_BIT_SET);
#define BEEP_OFF	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_7, GPIO_BIT_RESET);

#define RE				HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, GPIO_BIT_RESET);
#define DE				HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, GPIO_BIT_SET);




#define FILTER_A				0.8
#define	FILTER_B				1-FILTER_A

#define BR 115200
#define MBRXBUF_SIZE			25
#define MBTXBUF_SIZE			10
#define timer_period 			347

#define V_REF			3.3

#define GSAD_MODULE			1

enum {

	ON,
	OFF,
	FREE

} button;



	
uint8_t screen = 1;


typedef enum
{
    MB_ENOERR,                  /*!< no error. */
    MB_ENOREG,                  /*!< illegal register address. */
    MB_EINVAL,                  /*!< illegal argument. */
    MB_ETIMEDOUT                /*!< timeout error occurred. */
} ErrorCode;

uint8_t		MbRxBuf[MBRXBUF_SIZE];
uint8_t 	MbTxBuf[MBTXBUF_SIZE];
uint16_t	MbRxData[(MBRXBUF_SIZE+1)/2];


uint8_t cmddata[8];
uint8_t mbRCVData[9];

union Data
{
	uint8_t 	SLAVE_ADDR;
	uint8_t 	FUNC;
	uint16_t	START_REG_ADDR;
	uint16_t 	REG_NUM;
	uint16_t 	MBCRC16;
} DataPacket;

MbParam_t    PARAMS;

void MbParam_Init( void );
void uart_init( uint32_t baudrate );
void uart_send( uint8_t data );
uint8_t uart_recv( void );
void uart_rx_en( bool value );
void uart_tx_en( bool value );
void timer_start( void );
void timer_reset( void );
uint8_t get_int_sourse( void );

void timer_start( void );
uint8_t get_int_sourse( void );
void timer_reset( void );
void uart_init( uint32_t baudrate );
uint8_t uart_recv( void );
void uart_rx_en( bool value  );
void uart_tx_en( bool value );
void uart_send( uint8_t data  );
void mb_msg_wait( lpMbParam_t mbParam );



void UART_Wait( void );





uint8_t button1;
uint8_t button_up;
uint8_t button_down;
uint32_t tickcounter;
uint32_t brt_counter;
bool brt_flag = true;

int button1_state = OFF;
int button_up_state = OFF;
int button_down_state = OFF;
uint32_t iu = 0;

bool alarm_flag = false;



float Battery_V = 0;

void SystemClock_Config(void);
bool Check_Button1( void );
bool Check_ButtonUP( void );
bool Check_ButtonDOWN( void );
float Vbat_Filter( uint32_t v_bat, float yn );


#ifdef GSAD_MODULE

		GSAD_Params  GSAD_Module;

#endif	//GSAD_MODULE




int main(void)
{ 

	
//	HAL_NVIC_EnableIRQ( SysTick_IRQn );
	//SystemClock_Config();
	
  HAL_Init();

  /* Configure the system clock */
  SystemClock_Config();

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_ADC1_Init();
  MX_SPI2_Init();
  MX_TIM1_Init();
  MX_TIM3_Init();
  MX_TIM16_Init();
  MX_TIM17_Init();
  MX_USART1_UART_Init();
	MX_TIM4_Init();
  //MX_USART3_UART_Init( baudrate );

	
	//////////////////////////////////////////////////////////////////			IWDG
//	IWDG_HandleTypeDef hiwdg;
//	
//	hiwdg.Instance = IWDG;
//  hiwdg.Init.Prescaler = IWDG_PRESCALER_4;
//  hiwdg.Init.Reload = 4095;
//  HAL_IWDG_Init(&hiwdg);
//	

	
	
	
	///////////////////////////////////////////////////////////////////
	
	
	
	uint8_t adcenablestatus =  ADC_Enable( &hadc1 );
	
	__enable_irq();
	
	//Disp_Set();
	
	MbParam_Init();
	mbInit(&PARAMS);
	
	HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_4);
	//Disp_Init();
	NVIC_EnableIRQ(USART3_IRQn);
	__HAL_UART_ENABLE_IT(&huart3, UART_IT_RXNE);
	
	
	NVIC_EnableIRQ(TIM4_IRQn);

	DISP_ON;
	HAL_Delay(500);
	
	DISP_RESET_ON;
	__nop();
	DISP_RESET_OFF;
	
	
	#ifdef USE_DEMO
		LCD_initial();
	#endif
	
	PCD_ON;

	
	
	//Write( DISP_DATA, 0x23);
	int x = 0;
	int y = 0;
	
	char buf[32] = "Координаты точки: ";
	char le = ' ';
	int len;
	
	

	
	
	begin_display();
	
  while (1)
  {
		uint8_t ggg = 0x23;
		
		//uint32_t u_adc;		
	Battery_V = HAL_ADC_GetValue( &hadc1) * V_REF*2*100/4.5/(1 << 12);
	
	//Battery_V = Vbat_Filter( u_adc, Battery_V );
	HAL_Delay(1000);
	
	uint8_t adcstat = HAL_ADC_Start( &hadc1 );
	if( GSAD_Module.Is_Params)
	{
	uint8_t alrm = ALARM_GSAD(&GSAD_Module);
		
		if(alrm)
		{
				BEEP_ON;
			last_screen(alrm);
			alarm_flag = true;
		
		}
		else{
			BEEP_OFF;
			alarm_flag = false;
		}
	}	
		
			#ifdef USE_DEMO


			#ifdef GSAD_MODULE

			if(!GSAD_Module.Is_Connected)
			{
				
				
					GSAD_Module.Is_Connected = GSAD_Ans( PARAMS );
							if(!GSAD_Module.Is_Connected)
								GSAD_Connect_Check( &PARAMS  );
							else
							{
								if(screen == 1)
								{
										first_screen(FOUND, 0, 0, Battery_V);
								}
								
								Read_GSAD_Data( &PARAMS, &GSAD_Module );	
								HAL_Delay(1000);
							};
							

			};
			
			if( GSAD_Module.Is_Connected && !GSAD_Module.Is_Params )
			{
								

				//mb_msg_wait( &PARAMS );
				Get_GSAD_Data( &PARAMS, &GSAD_Module );
				Read_GSAD_Data( &PARAMS, &GSAD_Module );	
			};
			
			if( GSAD_Module.Is_Connected && GSAD_Module.Is_Params )
			{
				if(screen == 1)
					{
						if(!alarm_flag)
						first_screen(READY, 0, 0, Battery_V);
					}
				if(screen == 2)
				{
					if(!alarm_flag)
					second_screen(GSAD_Module.GSAD_TEMP_Value, GSAD, GSAD_Module.GSAD_Pos_Value, GSAD_Module.GSAD_Neg_Value);
				
				}
					
				
				
				Get_GSAD_Data( &PARAMS, &GSAD_Module );
				Read_GSAD_Data( &PARAMS, &GSAD_Module );	
			
			};
			
			
		
		#endif			// GSAD_MODULE
		
		
		
		

		
			#endif




  }

}

/** System Clock Configuration
*/
void SystemClock_Config(void)
{

  RCC_OscInitTypeDef RCC_OscInitStruct;
  RCC_ClkInitTypeDef RCC_ClkInitStruct;
  RCC_PeriphCLKInitTypeDef PeriphClkInit;

  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL2;
  HAL_RCC_OscConfig(&RCC_OscInitStruct);

  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;
  HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0);

  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_ADC;
  PeriphClkInit.AdcClockSelection = RCC_ADCPCLK2_DIV2;
  HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit);

  HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/1000);

  HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);

  /* SysTick_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);
	HAL_NVIC_SetPriority(USART3_IRQn, 1, 0);
	HAL_NVIC_SetPriority(TIM4_IRQn, 1, 0);
	SystemCoreClockUpdate();
}

/* USER CODE BEGIN 4 */


bool Check_Button1( void )
{

		if( HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0) == GPIO_PIN_SET)
			return true;
		else
			return false;

};


bool Check_ButtonUP( void )
{

		if( HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_5) == GPIO_PIN_SET)
			return true;
		else
			return false;

};
bool Check_ButtonDOWN( void )
{

		if( HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_4) == GPIO_PIN_SET)
			return true;
		else
			return false;

};




void SysTick_Handler( void )
{

	
	HAL_IncTick();
  HAL_SYSTICK_IRQHandler();
	
	tickcounter++;
	brt_counter++;
	
	
	
	
	if(brt_counter >= 8000)
	{
				
			brt_flag = false;
			brt_counter = 0;
	}
		
	if(!brt_flag)
	{
	
		///off
		TIM3->CCR4 = 0;
	
	}
	else
	{
		TIM3->CCR4 = 0x7F;
	}
	
	
	if(tickcounter % 100 == 0)
	{
		button1 = button1 << 1;
		button_down = button_down << 1;
		button_up = button_up << 1;
	
		if( !Check_Button1() )
			button1 |= 1;
		
		if( !Check_ButtonUP())
			button_up |= 1;
		
		if( !Check_ButtonDOWN())
			button_down |=1;
		
		
		
	};
	
	
	if( button1 == 0xFF && button1_state == OFF)
	{
		GSA_ON;
		button1_state = ON;
		button1 = 0;
		brt_flag = true;
		brt_counter = 0;
	};
	
	
	if(	button1 == 0xFF && button1_state == ON)
	{
		GSA_OFF;
		button1_state = OFF;
		button1= 0;
		//BEEP_OFF;
		brt_flag = true;
		brt_counter = 0;
	}
	
	if(button_up == 0xFF)
	{
		brt_flag = true;
		brt_counter = 0;
	
		if( button_up_state == OFF )
		{
			button_up_state = ON;
			button_up = 0;
			screen++;
			if(screen > 2)
				screen = 1;
			////// сменить экран
		}
		else
		{
		
			button_up_state = OFF;
			button_up = 0;
		
		}
	
	}
	
	
	if( button_down == 0xFF )
		{
		brt_flag = true;
			brt_counter = 0;
	
		if( button_down_state == OFF )
		{
			button_down_state = ON;
			button_down = 0;
			
			screen--;
			if(screen < 1)
				screen = 2;
			
			////// сменить экран
		}
		else
		{
		
			button_down_state = OFF;
			button_down = 0;
		
		}
	
	}
	
	
	
	
};





void ADC1_IRQHandler( void )
{
	uint32_t adcval;
	adcval = HAL_ADC_GetValue( &hadc1);
	
};

float  Vbat_Filter( uint32_t v_bat, float yn )
{
		 
	
 		return (FILTER_A * yn + FILTER_B * (float)v_bat);

};









/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void MbParam_Init( void )
{

	PARAMS.address = 0;
	PARAMS.function = 0;
	PARAMS.num_regs = 0;
	PARAMS.stopBits = 1;
	PARAMS.serialBaudrate = bps115200;
	
	
	PARAMS.rxBuf = MbRxBuf;
	PARAMS.rxBufSize = MBRXBUF_SIZE;
	PARAMS.rxCount = 0;
	PARAMS.rxData = MbRxData;
	
	PARAMS.txBuf = MbTxBuf;
	PARAMS.txBufSize = MBTXBUF_SIZE;
	PARAMS.txCount = 0;
	PARAMS.txIndex = 0;
	
	PARAMS.timeLeft = 0;
	PARAMS.timeOut = 0;
	PARAMS.timer_set = timer_period;
	
	///////
	PARAMS.lpUartInit = uart_init;
	PARAMS.lpUartSend = uart_send;
	PARAMS.lpUartRecv = uart_recv;
	
	PARAMS.lpSetRxEn = uart_rx_en;
	PARAMS.lpSetTxEn = uart_tx_en;
	
	PARAMS.lpTimerStart = timer_start;
	PARAMS.lpTimerReset = timer_reset;
	PARAMS.GetIntSourse = get_int_sourse;
	///////
	
	
	PARAMS.Flags.enableTimer = 0;
	PARAMS.Flags.enableParseRxData = 0;
	PARAMS.Flags.isParsedStart = 0;
	PARAMS.Flags.isRxDataMain = 0;
	PARAMS.Flags.isHostTimeout = 0;
	PARAMS.Flags.isConfigChangeLock = 0;
	PARAMS.Flags.eepromNeedUpdate = 0;
	PARAMS.Flags.isPasswordValid = 0;
	PARAMS.Flags.isPacket = 0;

};



void	USART3_IRQHandler(void)
{
	
		HAL_UART_IRQHandler( &huart3 );

		//mb_rx_tx_interrupt(&PARAMS);
		
		return;
};	

static uint8_t mbMasterItFlag = 0; 
volatile int rxCount = 0;
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) {
		if( huart->Instance == USART3 ) {
				mbMasterItFlag = RxInt;
				rxCount++;
				mb_rx_tx_interrupt(&PARAMS);
		}
}

void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart)
{
		if( huart->Instance == USART3 ) {
				mbMasterItFlag = TxInt;
				mb_rx_tx_interrupt(&PARAMS);
		}
}

void TIM4_IRQHandler(void)
{
		if(__HAL_TIM_GET_IT_SOURCE( &htim4, TIM_IT_UPDATE) !=RESET)
    {
				__HAL_TIM_CLEAR_IT( &htim4, TIM_IT_UPDATE);
    }	
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_15, 1);
		//TIM_ClearIntPending(LPC_TIM1, TIM_MR1_INT);
		mb_Timer_Int(&PARAMS);
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_15, 0);
		
		return;

};

void timer_start( void )
{
		TIM4->CNT= 0;											// сброс счетчика
		HAL_TIM_Base_Start_IT(&htim4);

};
void timer_reset( void )
{
			TIM4->CNT = 0;										// сброс счетчика
			//HAL_TIM_Base_Stop_IT(&htim4);				


};
uint8_t get_int_sourse( void )
{



//	uint32_t mbIIRStatus = USART3->SR;
//		uint8_t mb_int_sourse = 0;


//		if(mbIIRStatus & (1 << 6))			//TXE
//		//if(mbIIRStatus == 0xC0)
//		{		
//				mb_int_sourse = TxInt;
//				//mb_int_sourse = 0x10;
//		};
//		
//		if(mbIIRStatus & (1 << 5))		//Received data is ready to be read
//		{
//				mb_int_sourse = RxInt;
//				//mb_int_sourse  = 0x01;
//		};
//		
//		return mb_int_sourse;


	return mbMasterItFlag;

};

void uart_init( uint32_t baudrate )
{

	
	MX_USART3_UART_Init( baudrate );
	
		/* Enable the UART Parity Error Interrupt */
    __HAL_UART_ENABLE_IT(&huart3, UART_IT_PE);

    /* Enable the UART Error Interrupt: (Frame error, noise error, overrun error) */
    __HAL_UART_ENABLE_IT(&huart3, UART_IT_ERR);

    /* Enable the UART Data Register not empty Interrupt */
    __HAL_UART_ENABLE_IT(&huart3, UART_IT_RXNE);
};
uint8_t uart_recv( void )
{

	UART_Wait();
	uint8_t rc_data;
	if( HAL_UART_Receive( &huart3, &rc_data, 1, 100) != HAL_OK ) {
		rc_data = 0xFF;
	}
	
	return rc_data;
};
void uart_rx_en( bool value  )
{

//	if(value)
//		{RE;}			
//	else
//		DE;		//DE;

};
void uart_tx_en( bool value )
{
		
	if( value )
		{DE;}			//DE
	else {
		RE;
		// ???????????????????????????????????????????????
		/* Enable the UART Parity Error Interrupt */
    __HAL_UART_ENABLE_IT(&huart3, UART_IT_PE);

    /* Enable the UART Error Interrupt: (Frame error, noise error, overrun error) */
    __HAL_UART_ENABLE_IT(&huart3, UART_IT_ERR);

    /* Enable the UART Data Register not empty Interrupt */
    __HAL_UART_ENABLE_IT(&huart3, UART_IT_RXNE);
		
		
		RE;
	}

};
void uart_send( uint8_t data  )
{

	
	UART_Wait();
	
	HAL_UART_Transmit_IT( &huart3, &data, 1);

};


void UART_Wait( void )
{
				
				while(HAL_UART_GetState( &huart3 ) == HAL_UART_STATE_BUSY)
				{};

};




void mb_msg_wait( lpMbParam_t mbParam )
{

	while( !mbParam->Flags.isRecvPacket);

};





/* USER CODE END 4 */

#ifdef USE_FULL_ASSERT

/**
   * @brief Reports the name of the source file and the source line number
   * where the assert_param error has occurred.
   * @param file: pointer to the source file name
   * @param line: assert_param error line source number
   * @retval None
   */
void assert_failed(uint8_t* file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
    ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */

};

#endif

/**
  * @}
  */ 

/**
  * @}
*/ 



/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/;
