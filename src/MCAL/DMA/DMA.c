/*
*File: Source File of DMA
*Author:  Fatma Ezzat
*Created:  13/4/2024
*Target:  STM32F401cc
*/

/**************************************************************/
/*                          Notes                             */
/**************************************************************/
/*
* We have 2 DMA Peripherals in STM. 
* Each DMA has 8 streams and every stream can be connected to either 8 multiplexed channels 
* or to memory for data transfer.
* We refer to source as a peripheral and destination as a memory.
* The memeory is connected to a stream while the peripheral is connected to a channel in a stream. 
* In case We transfer data from memory to memeory we need to make some configuration such as:
* 1- Channel will be equal Zero
* 2- Disable Direct Mode bec We will use FIFO buffer 
*/
/********************************************************************************************************/
/************************************************Includes************************************************/
/********************************************************************************************************/
#include "DMA.h"
#include "DMA_Validation.h"


/********************************************************************************************************/
/************************************************Defines*************************************************/
/********************************************************************************************************/

/*Base Address of 2 DMA on AHB bus */
#define BASE_ADDRESS_OF_DMA1    0x40026000   
#define BASE_ADDRESS_OF_DMA2    0x40026400   
#define NUM_OF_DMA              2

/*Every DMA Peripheral has 8 streams */
#define NUM_OF_STREAMS     8

/*Every stream has 8 channels */
#define NUM_OF_CHANNELS    8

#define DMA1_Add  ((volatile DMA_REG *const)(BASE_ADDRESS_OF_DMA1))
#define DMA2_Add  ((volatile DMA_REG *const)(BASE_ADDRESS_OF_DMA2))


#define CLR_REG_MASK        0X00000000
#define CLR_INT_FLAGS       0xffffffff

/********************************************************************************************************/
/************************************************Types***************************************************/
/********************************************************************************************************/
/*For Every Stream*/
typedef struct 
{
    u32 SxCR;       /*Stream x configuration register*/
    u32 SxNDTR;     /*Stream x number of data register*/
    u32 SxPAR;      /*Stream x peripheral address register*/
    u32 SxM0AR;     /*Stream x memory 0 address register*/
    u32 SxM1AR;     /*Stream x memory 1 address register*/
    u32 SxFCR;      /*Stream x FIFO control register*/

}Stream_REG;

/*For Every DMA peripheral*/
typedef struct 
{
    u32 LISR;       /*Low interrupt status register*/
    u32 HISR;       /*High interrupt status register*/
    u32 LIFCR;      /*Low interrupt flag clear register*/
    u32 HIFCR;      /*High interrupt flag clear register*/
    Stream_REG streamReg[NUM_OF_STREAMS];
}DMA_REG;






/********************************************************************************************************/
/************************************************Variables***********************************************/
/********************************************************************************************************/
volatile DMA_REG *const ArrOfDMA[NUM_OF_DMA] ={ DMA1_Add , DMA2_Add};
extern StreamConfiguration STREAM0_Req;

/********************************************************************************************************/
/*****************************************Static Functions Prototype*************************************/
/********************************************************************************************************/



/********************************************************************************************************/
/*********************************************APIs Implementation****************************************/
/********************************************************************************************************/
extern StreamConfiguration STREAM0_Req;

DMA_enuErrorStatus DMA_initStream(void){

    /*************************************** Validation Part ********************************************/
    DMA_enuErrorStatus ReturnError = DMA_enumOk;

    /*Check on Number of DMA in MC*/
    if (STREAM0_Req.DMA_Num >NUM_OF_DMA){ ReturnError =DMA_enumWrongcConfiguration;}

    /*Check on Number of Strams in the DMA*/
    else if (STREAM0_Req.Stream_Num >NUM_OF_STREAMS){ ReturnError = DMA_enumWrongcConfiguration; }

    /*Check on Number of Channels in the stream*/
    else if(STREAM0_Req.Channel_Num>NUM_OF_CHANNELS){ ReturnError = DMA_enumWrongcConfiguration; }

    /*Check on Priority Level*/
    else if (STREAM0_Req.Priority_level>PRIORITY_VERY_HIGH){ReturnError = DMA_enumWrongcConfiguration; }

    /*Check on Memeory increment mode*/
    else if(STREAM0_Req.Memory_increment_mode>MEMORY_ADDRESS_PTR_INCR){ReturnError = DMA_enumWrongcConfiguration;}

    /*Check on Peripheral increment mode*/
    else if(STREAM0_Req.Peripheral_increment_mode>PERIPHERAL_ADDRESS_PTR_INCR){ReturnError = DMA_enumWrongcConfiguration;}

    /*Check on Memory Data Size*/
    else if(STREAM0_Req.Memory_data_size>MEMORY_WORD_32BITS){ReturnError = DMA_enumWrongcConfiguration;}

    /*Check on Peripheral Data Size*/
    else if(STREAM0_Req.Peripheral_data_size>PERIPHERAL_WORD_32BITS){ReturnError = DMA_enumWrongcConfiguration;}

    /*Check on Data transfer direction*/
    else if(STREAM0_Req.Data_Direct_mode>MEMORY_TO_MEMORY){ReturnError = DMA_enumWrongcConfiguration;}

    /*Check on FIFO threshold selection*/
    else if(STREAM0_Req.FIFO_threshold_selection>FULL_FIFO){ReturnError = DMA_enumWrongcConfiguration;}

    /***************************************** Implementation Part ************************************************/
    else{
         /*1- Before any Configuration we need to ensure that the Enable bit is disabled 
        so that if it is enabled, We need tto clear it and wait until  it becomes Zero */
        if((ArrOfDMA[STREAM0_Req.DMA_Num]->streamReg[STREAM0_Req.Stream_Num].SxCR >>EN)&1){
            /*Clear it */
            ArrOfDMA[STREAM0_Req.DMA_Num]->streamReg[STREAM0_Req.Stream_Num].SxCR &=~(ENABLE<<EN);
            while ((ArrOfDMA[STREAM0_Req.DMA_Num]->streamReg[STREAM0_Req.Stream_Num].SxCR >>EN)&1);

        }else{
            /*Noting To DO*/
         }

        /*2- Select the channel in case We connect it with peripheral*/
        u32 Loc_SxCRTemp =  ArrOfDMA[STREAM0_Req.DMA_Num]->streamReg[STREAM0_Req.Stream_Num].SxCR;
        u32 Loc_SxFCRTemp = ArrOfDMA[STREAM0_Req.DMA_Num]->streamReg[STREAM0_Req.Stream_Num].SxFCR;

        Loc_SxCRTemp &= CLR_REG_MASK;
        Loc_SxFCRTemp &= CLR_REG_MASK; 

        Loc_SxCRTemp |=((STREAM0_Req.Channel_Num)<<CHSEL);

        /*3- Select Priority Level*/
        Loc_SxCRTemp |= ((STREAM0_Req.Priority_level)<<PL);

        /*4- Select Direction Mode */
        Loc_SxCRTemp |= ((STREAM0_Req.Data_transfer_direction)<<DIR);

        /*5- Select Data size for Peripheral and Memory */
        Loc_SxCRTemp |=((STREAM0_Req.Peripheral_data_size)<<PSIZE);
        Loc_SxCRTemp |=((STREAM0_Req.Memory_data_size)<<MSIZE);
    
        /*6- Select Increment mode for Peripheral and Memory*/
        Loc_SxCRTemp |= ((STREAM0_Req.Peripheral_increment_mode)<<PINC);
        Loc_SxCRTemp |= ((STREAM0_Req.Memory_increment_mode)<<MINC);

        /*7- Select Enable Interrupts */
        /*Enable Transfer complete interrupt and Half transfer interrupt*/
        Loc_SxCRTemp |= (ENABLE<<HTIE);
        Loc_SxCRTemp |= (ENABLE<<TEIE);

        /*Disable Direct Mode*/
        Loc_SxFCRTemp |=(STREAM0_Req.Data_Direct_mode<<DMDIS);

        /*Select  FIFO threshold*/
        Loc_SxFCRTemp |=(STREAM0_Req.FIFO_threshold_selection<<FTH);

        ArrOfDMA[STREAM0_Req.DMA_Num]->streamReg[STREAM0_Req.Stream_Num].SxCR =  Loc_SxCRTemp;
        ArrOfDMA[STREAM0_Req.DMA_Num]->streamReg[STREAM0_Req.Stream_Num].SxFCR=  Loc_SxFCRTemp;
   }

   return ReturnError;
}

DMA_enuErrorStatus DMA_SetAddressInSingleBuffer(u8 DMA_Num,STREAM_Request* data){

    /*************************************** Validation Part ********************************************/
    DMA_enuErrorStatus ReturnError = DMA_enumOk;

    /*Check on DMA number*/
    if (DMA_Num >NUM_OF_DMA){ ReturnError = DMA_enumWrongcConfiguration; }

    /*Check on Pointer of the stream request*/
    else if (!data){ReturnError = DMA_enumNullPointer; }

    /***************************************** Implementation Part ************************************************/
    else
    {
        /*1- Set the pheripheral address*/
        ArrOfDMA[DMA_Num]->streamReg[data->Stream].SxPAR = (u32)data->Peripheral_Address;

        /*2- Set the memory 0 address*/
        ArrOfDMA[DMA_Num]->streamReg[data->Stream].SxM0AR = (u32)data->Memory_0_Address;

        /*3- Set Block length*/
        ArrOfDMA[DMA_Num]->streamReg[data->Stream].SxNDTR = data->Block_Length;
    }
       return ReturnError;
}
DMA_enuErrorStatus DMA_SetAddressInDoubleBuffer(u8 DMA_Num, STREAM_Request* data){

   /*************************************** Validation Part ********************************************/
    DMA_enuErrorStatus ReturnError = DMA_enumOk;

    /*Check on DMA number*/
    if (DMA_Num >NUM_OF_DMA){ ReturnError = DMA_enumWrongcConfiguration; }

    /*Check on Pointer of the stream request*/
    else if (!data){ReturnError = DMA_enumNullPointer; }

    /***************************************** Implementation Part ************************************************/
    else
    {
        /*1- Set the pheripheral address*/
        ArrOfDMA[DMA_Num]->streamReg[data->Stream].SxPAR = (u32)data->Peripheral_Address;

        /*2- Set the memory 0 address*/
        ArrOfDMA[DMA_Num]->streamReg[data->Stream].SxM0AR = (u32)data->Memory_0_Address;

        /*3- Set the memory 1 address*/
        ArrOfDMA[DMA_Num]->streamReg[data->Stream].SxM1AR = (u32)data->Memory_1_Address;

        /*4- Set Block length*/
        ArrOfDMA[DMA_Num]->streamReg[data->Stream].SxNDTR = data->Block_Length;

        /*5- Activate  Double buffer mode*/
        ArrOfDMA[DMA_Num]->streamReg[data->Stream].SxCR |=(ENABLE<<DBM); 

    }
       return ReturnError;
}

DMA_enuErrorStatus DMA_Enable(u8 DMA_Num,u8 stream){

    
   /*************************************** Validation Part ********************************************/
    DMA_enuErrorStatus ReturnError = DMA_enumOk;

    /*Check on the DMA number*/
    if (DMA_Num >NUM_OF_DMA){ ReturnError = DMA_enumWrongcConfiguration; }

    /*Check on the stream number*/
    else if (stream > NUM_OF_STREAMS){ ReturnError = DMA_enumWrongcConfiguration; }

    /***************************************** Implementation Part ************************************************/
    else
    {
        /*First, We need to clear all flags before setting the enable bit*/
        /*Clear transfer complete interrupt flag*/
        if(stream<NUM_OF_STREAMS){

            ArrOfDMA[DMA_Num]->LIFCR |= (INT_CLR<<stream);

        }else if((stream>=NUM_OF_STREAMS)&&( stream >=(2*NUM_OF_STREAMS))){

            ArrOfDMA[DMA_Num]->HIFCR &= (CLR_INT_FLAGS<<(stream-NUM_OF_STREAMS)*4);
        }
     
        /*Finally, Enable the stream*/
        ArrOfDMA[DMA_Num]->streamReg[stream].SxCR |=(ENABLE<<EN);
    }
     return ReturnError;
}


DMA_enuErrorStatus DMA_GetInterruptCBFunc(Transfer_completeCB tcCB, Half_transferCB htcCB){

    /*************************************** Validation Part ********************************************/
    DMA_enuErrorStatus ReturnError = DMA_enumOk;

    /*Check on the pointer to transfer complete callback function*/
    if (!tcCB){ ReturnError =DMA_enumNullPointer;}

    /*Check on the pointer to half transfer complete callback function*/
    else if (!htcCB){ ReturnError =DMA_enumNullPointer;}

    /***************************************** Implementation Part ************************************************/
    else
    {
        STREAM0_Req.CompTransCB = tcCB;
        STREAM0_Req.HalfCompTransCB =htcCB;
    }
    return ReturnError;
}


/*****************************************************************************************************************************************/
/************************************************************************/
/*					          USART Handlers                            */
/************************************************************************/
 void DMA2_Stream0_IRQHandler(void){

    /*Check on Transfer complete interrupt flag*/
    if(((ArrOfDMA[DMA2]->LISR & (1<<TCIF) )>>TCIF)== 1 ){
        /*Clear Transfer complete interrupt flag*/
        ArrOfDMA[DMA2]->LIFCR &=~(1<<TCIF) ;

        STREAM0_Req.CompTransCB();
    }
    /*Check on Half Transfer complete interrupt flag*/
    if(((ArrOfDMA[DMA2]->LISR & (1<<HTIF) )>>HTIF)== 1)
    {
        /*Clear Half Transfer complete interrupt flag*/
        ArrOfDMA[DMA2]->LIFCR &=~(1<<HTIF) ;

        STREAM0_Req.HalfCompTransCB();
    }


}

