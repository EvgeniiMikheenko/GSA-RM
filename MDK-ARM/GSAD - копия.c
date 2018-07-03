#include "GSAD.h"





uint8_t read_cnt = 0;
uint16_t addr_array[] = {GSAD_State0_Pos_Tresh_addr, GSAD_State0_Neg_Tresh_addr, GSAD_State0_Pos_Tresh_Danger_addr, GSAD_State0_Neg_Tresh_Danger_addr, GSAD_TEMP_Value_addr, GSAD_Ass_Value_addr, GSAD_HV_addr, GSAD_Pos_Value_addr, GSAD_Neg_Value_addr};


//GSAD_Params GSAD;



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




void Read_GSAD_Data( MbParam_t mbParam, GSAD_Params arg )
{

		if(mbParam.Flags.isCRCValid && mbParam.Flags.isRecvPacket)
		{
			uint16_t recv_byte = (((mbParam.rxBuf[3] << 8) + mbParam.rxBuf[4]));
			
			uint16_t reg_addr	 = (((mbParam.txBuf[2] << 8) + mbParam.txBuf[3]));
			
	
	
	
//#define	GSAD_TEMP_Value_addr				0x4B			//96
//#define	GSAD_Ass_Value_addr					0x4A			//94
//#define	GSAD_HV_addr								0x49			//92
//#define	GSAD_Pos_Value_addr					0x47			//8E
//#define	GSAD_Neg_Value_addr					0x48			//90




//#define	GSAD_State0_Pos_Tresh_addr					0x04		//08
//#define	GSAD_State0_Neg_Tresh_addr					0x05		//0A
//#define	GSAD_State0_Pos_Tresh_Danger_addr		0x07		//0E
//#define	GSAD_State0_Neg_Tresh_Danger_addr		0x08		//10
	
		if(!arg.Is_Params)
		{
			bool ans1 = Slave_request( &mbParam, GSAD_addr, 0x03, GSAD_State0_Pos_Tresh_addr, 0x05);		//чтение  параметров
			arg.Is_Params = true;
			
		}
		else
		{
			bool ans1 = Slave_request( &mbParam, GSAD_addr, 0x03, GSAD_State0_Pos_Tresh_addr, 0x05);		//чтение  данных
			
		}
			
			

			
			
		};		

		

};

