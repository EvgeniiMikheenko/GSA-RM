#ifndef GSAD_H
#define GSAD_H



#include <stdint.h>
#include <stdbool.h>
#include "modbs_master.h"







#define	GSAD_DEVICE		0x01


#define	GSAD_addr							0x01
#define GSAD_Device_addr			0x63			//C6

#define	GSAD_State0_Pos_Tresh_addr					0x04		//08
#define	GSAD_State0_Neg_Tresh_addr					0x05		//0A
#define	GSAD_State0_Pos_Tresh_Danger_addr		0x07		//0E
#define	GSAD_State0_Neg_Tresh_Danger_addr		0x08		//10


#define	GSAD_TEMP_Value_addr				0x4B			//96
#define	GSAD_Ass_Value_addr					0x4A			//94
#define	GSAD_HV_addr								0x49			//92
#define	GSAD_Pos_Value_addr					0x47			//8E
#define	GSAD_Neg_Value_addr					0x48			//90


typedef struct 
{

uint16_t	GSAD_State0_Pos_Tresh;
uint16_t	GSAD_State0_Neg_Tresh;
uint16_t	Dummy;	
uint16_t	GSAD_State0_Pos_Tresh_Danger;
uint16_t	GSAD_State0_Neg_Tresh_Danger;	
	
	
uint16_t	GSAD_TEMP_Value;
uint16_t	GSAD_Ass_Value;
uint16_t	GSAD_HV;
uint16_t	GSAD_Pos_Value;
uint16_t	GSAD_Neg_Value;
	
bool		Is_Connected;
bool 		Is_Params;
	
}GSAD_Params;


//uint16_t addr_array[] = {GSAD_State0_Pos_Tresh_addr, GSAD_State0_Neg_Tresh_addr, GSAD_State0_Pos_Tresh_Danger_addr, GSAD_State0_Neg_Tresh_Danger_addr, GSAD_TEMP_Value_addr, GSAD_Ass_Value_addr, GSAD_HV_addr, GSAD_Pos_Value_addr, GSAD_Neg_Value_addr};



void GSAD_Connect_Check( lpMbParam_t Param );


bool GSAD_Ans ( MbParam_t mbParam );

void Read_GSAD_Data( MbParam_t mbParam, GSAD_Params arg );
#endif	//GSAD_H