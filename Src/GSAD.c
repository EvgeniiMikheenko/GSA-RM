#include "GSAD.h"





uint8_t read_cnt = 0;
uint16_t addr_array[] = {GSAD_State0_Pos_Tresh_addr, GSAD_State0_Neg_Tresh_addr, GSAD_State0_Pos_Tresh_Danger_addr, GSAD_State0_Neg_Tresh_Danger_addr, GSAD_TEMP_Value_addr, GSAD_Ass_Value_addr, GSAD_HV_addr, GSAD_Pos_Value_addr, GSAD_Neg_Value_addr};


//GSAD_Params GSAD;

const uint16_t divider = 0xFFFF/3300;


void GSAD_Connect_Check( lpMbParam_t mbParam )
{

	bool ans = Slave_request( mbParam, GSAD_addr, 0x03, GSAD_Device_addr, 0x01);
	
};

bool GSAD_Ans ( MbParam_t mbParam )
{
	
	
	uint16_t reg_device = (mbParam.rxBuf[3] << 8) + mbParam.rxBuf[4];
	
	if(mbParam.Flags.isCRCValid && mbParam.Flags.isRecvPacket &&  (reg_device == GSAD_DEVICE))
	{

		return true;

	}
	else
	{
			return false;
	}
	
	
	
};




void Read_GSAD_Data( lpMbParam_t mbParam, GSAD_Params *arg )
{

//#define	GSAD_TEMP_Value_addr				0x4B			//96
//#define	GSAD_Ass_Value_addr				0x4A			//94
//#define	GSAD_HV_addr								0x49			//92
//#define	GSAD_Pos_Value_addr					0x47			//8E
//#define	GSAD_Neg_Value_addr					0x48			//90
//#define	GSAD_State0_Pos_Tresh_addr					0x04		//08
//#define	GSAD_State0_Neg_Tresh_addr					0x05		//0A
//#define	GSAD_State0_Pos_Tresh_Danger_addr		0x07		//0E
//#define	GSAD_State0_Neg_Tresh_Danger_addr		0x08		//10
		if(!arg->Is_Params)
		{
			bool ans1 = Slave_request( mbParam, GSAD_addr, 0x03, GSAD_State0_Pos_Tresh_addr, 0x05);		//чтение  параметров
		}
		else
		{
			bool ans1 = Slave_request( mbParam, GSAD_addr, 0x03, GSAD_Pos_Value_addr, 0x05);		//чтение  данных
		}
				
};
uint8_t tmp = 0;
void Get_GSAD_Data( lpMbParam_t mbParam, GSAD_Params *arg )
{
		if(!arg->Is_Params)
		{
			arg->GSAD_State0_Pos_Tresh = mbParam->rxData[0];
			arg->GSAD_State0_Neg_Tresh = mbParam->rxData[1];
			arg->GSAD_State0_Pos_Tresh_Danger = mbParam->rxData[3];
			arg->GSAD_State0_Neg_Tresh_Danger = mbParam->rxData[4];
			if( tmp > 2 )
				arg->Is_Params = 1;
			else
				tmp++;
		}
		else
		{
		
			arg->GSAD_Pos_Value = mbParam->rxData[0];
			arg->GSAD_Neg_Value = mbParam->rxData[1];
			arg->GSAD_HV = mbParam->rxData[2];
			arg->GSAD_Ass_Value = mbParam->rxData[3];
			arg->GSAD_TEMP_Value = mbParam->rxData[4];
		
		};
			
		

};


uint8_t ALARM_GSAD( GSAD_Params *arg )
{

		uint16_t pos = arg->GSAD_Pos_Value/divider;
		uint16_t neg = arg->GSAD_Neg_Value/divider;
	
	
		if(pos >= arg->GSAD_State0_Pos_Tresh_Danger )
			return POS_TRESH_DANGER;
		if(neg >= arg->GSAD_State0_Neg_Tresh_Danger)
			return NEG_TRESH_DANGER;
		
		if(pos >= arg->GSAD_State0_Pos_Tresh)
			return POS_TRESH;
		
		if(neg >= arg->GSAD_State0_Neg_Tresh)
			return NEG_TRESH;
		
		return 0;


};



