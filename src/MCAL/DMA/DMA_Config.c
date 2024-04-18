/*
*File: 
*Author:  Fatma Ezzat
*Created:
*Target:  STM32F401cc
*/
/********************************************************************************************************/
/************************************************Includes************************************************/
/********************************************************************************************************/
#include "DMA.h"


void TurnON_Led_1(void);
void TurnON_Led_2(void);
/********************************************************************************************************/
/************************************************Variables***********************************************/
/*******************************************************************s*************************************/
volatile StreamConfiguration STREAM0_Req={
    .DMA_Num = DMA2,
    .Stream_Num = STREAM0,
    .Channel_Num =0,
    
    .Priority_level = PRIORITY_VERY_HIGH,
    .Memory_increment_mode =MEMORY_ADDRESS_PTR_INCR,
    .Peripheral_increment_mode = PERIPHERAL_ADDRESS_PTR_INCR,

    .Memory_data_size = MEMORY_WORD_32BITS,
    .Peripheral_data_size =PERIPHERAL_WORD_32BITS,

    .Data_transfer_direction = MEMORY_TO_MEMORY,
    .Data_Direct_mode = DATA_DIRECT_MODE_DISABLE ,

    .FIFO_threshold_selection = FULL_FIFO
};


