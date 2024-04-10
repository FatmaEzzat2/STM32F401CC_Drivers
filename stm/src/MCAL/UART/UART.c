/*
*File: Source File  of UART
*Author:  Fatma Ezzat
*Created: 4/7/2024
*Target:  STM32F401cc
*/
/********************************************************************************************************/
/************************************************Includes************************************************/
/********************************************************************************************************/
#include "UART.h"
#include "UART_Validation.h"

/********************************************************************************************************/
/************************************************Defines*************************************************/
/********************************************************************************************************/

#define NUM_OF_UARTS   3
#define MAX_DATA_LENGTH 255
/*Baud Rate Calculations*/
#define MAX_NUM_16_OVER_SAMPLE      16
#define MAX_NUM_8_OVER_SAMPLE        8

#define OVER_SAMPLING_BITS_SHIFT     4



/*Base Address of Registers*/
#define BASE_ADDRESS_OF_USART1      0x40011000
#define BASE_ADDRESS_OF_USART2      0x40004400
#define BASE_ADDRESS_OF_USART6      0x40011400

/*UART Types*/
#define  USART1_ADD    ((volatile USART_REG* const)(BASE_ADDRESS_OF_USART1))
#define  USART2_ADD    ((volatile USART_REG* const)(BASE_ADDRESS_OF_USART2))
#define  USART6_ADD    ((volatile USART_REG* const)(BASE_ADDRESS_OF_USART6))

/********************************************************************************************************/
/************************************************Types***************************************************/
/********************************************************************************************************/
typedef struct 
{
   u32 SR;      /*Status Register*/
   u32 DR;      /*Data Register*/
   u32 BBR;     /*Baud Rate Register*/
   u32 CR1;     /*Control Register 1*/
   u32 CR2;     /*Control Register 2*/
   u32 CR3;     /*Control Register 3*/
   u32 GTPR;    /*Guard time and prescaler Register*/
}USART_REG;
/********************************************************************************************************/
/************************************************Static Function*****************************************/
/********************************************************************************************************/
static void GetFractionandMantissa(f32 number,u16* mantissa ,f32* fraction){

   /*Get the decimal part of the number*/
   *mantissa = (u32)number;
   /*Get the  fraction part of the number*/
   *fraction = number - * mantissa;
}

/********************************************************************************************************/
/************************************************Variables***********************************************/
/********************************************************************************************************/

volatile USART_REG *const arrOfUARTS[NUM_OF_UARTS]={USART1_ADD,USART2_ADD,USART6_ADD};
TX_Req TXRequest[NUM_OF_UARTS] ={{.state = Ready},{.state = Ready},{.state = Ready} }; 
RX_Req RXRequest[NUM_OF_UARTS] ={{.state = Ready},{.state = Ready},{.state = Ready} };  
extern USART_initialize UART1_init;


/********************************************************************************************************/
/*********************************************APIs Implementation****************************************/
/********************************************************************************************************/
UART_enuErrorStatus USART_init(USART_initialize *init){

   UART_enuErrorStatus ReturnError = UART_enumOk;

   /***************************************Validation Part********************************************/
   if (!init){
      ReturnError = UART_enumNullPointer;
   /*Check on the USART Channel*/
   }else if((init->Channel) > USART6){
      ReturnError = UART_enumWrongcConfiguration;

   /*Check on the over sample mode*/
   }else if((init->Oversampling_mode) > OVER_SAMPLING_BY_8){
      ReturnError = UART_enumWrongcConfiguration;

   /*Check on the stop bits */
   }else if((init->StopBits) >STOP_BIT_3_2){
      ReturnError = UART_enumWrongcConfiguration;

   /*Check on the Parity mode*/
   }else if ((init->ParityControl)> PARTY_ENABLE_ODD)
   {
      ReturnError = UART_enumWrongcConfiguration;

   /*Check on the Word length*/
   }else if(( init->Word_length)>DATA_BITS_9){
      ReturnError = UART_enumWrongcConfiguration;
   }else{

   /************************************Implementation Part********************************************/

   /* USART Enable*/
   arrOfUARTS[init->Channel]->CR1 |=(ENABLE<<UE);

   /*Select Word length*/
   arrOfUARTS[init->Channel]->CR1 |=(init->Word_length<<M);

   /*Select Stop bits*/
   arrOfUARTS[init->Channel]->CR2 |=(init->StopBits<<STOP);

   /*Select Parity*/
   arrOfUARTS[init->Channel]->CR1 |=((init->ParityControl)<<PS);
   
   /*Baud Rate Calculations*/
   /*
   *Baud Rate = (F_ck)/8*(2-OVER8)*USART_DIV
   */
   f32 USARTDIV_calc = (f32)(init->frequncy)/(8*(2-(init->Oversampling_mode))*(init->BaudRate));
   f32 USART_Fraction ;
   u16 USART_Mantissa ;
   u32 Fraction_Calc;
   GetFractionandMantissa(USARTDIV_calc,&USART_Mantissa,&USART_Fraction);

   if (init->Oversampling_mode == OVER_SAMPLING_BY_16)
   {
         Fraction_Calc = USART_Fraction * MAX_NUM_16_OVER_SAMPLE;

         /*
         *if the fraction value exceeds 16, we'll need to add 1 to USART_Mantissa and subtract 16 from fraction value
         *because We assign the fraction value in 4 bits only (Max value =16)
         **/

         if(Fraction_Calc > OVER_SAMPLING_BY_16){
            Fraction_Calc -= OVER_SAMPLING_BY_16;
            USART_Mantissa++;      
         }
   }else{
         Fraction_Calc = USART_Fraction * MAX_NUM_8_OVER_SAMPLE;
         /*
         *if the fraction value exceeds 8, we'll need to add 1 to USART_Mantissa and subtract 8 from fraction value.
         *because We assign the fraction value in 3 bits only (Max value =8).
         */

         if(Fraction_Calc > MAX_NUM_8_OVER_SAMPLE){
            Fraction_Calc -= MAX_NUM_8_OVER_SAMPLE;
            USART_Mantissa++;

         }
   }
   /*Assign baud rate value in the register*/
   arrOfUARTS[init->Channel]->BBR = (USART_Mantissa<<OVER_SAMPLING_BITS_SHIFT) + Fraction_Calc+1;
   /*Enable Transmitter*/
   arrOfUARTS[init->Channel]->CR1 |=(ENABLE<<TE);
   /*Enable Receiver*/
   arrOfUARTS[init->Channel]->CR1 |=(ENABLE<<RE);
   }


   return ReturnError;
}
/*****************************************************************************************************************************************/
UART_enuErrorStatus USART_sendBufferAsyncZeroCopy(u8 USART_id,u8* dataOfBuffer,u8 length, TX_CB cb)
{
   UART_enuErrorStatus ReturnError = UART_enumOk;

   /***************************************Validation Part********************************************/
   /*Check on the USART Channel*/
   if(USART_id > USART6){
      ReturnError = UART_enumWrongcConfiguration;

   /*Check on the pointer of Data Buffer*/
   }else if(!dataOfBuffer){
      ReturnError = UART_enumNullPointer;

   /*Check on the Data length*/
    }else if(length > MAX_DATA_LENGTH){
      ReturnError = UART_enumWrongDataLength;

   /************************************Implementation Part********************************************/
   }else{

      if (TXRequest[USART_id].state == Ready)
      {
         TXRequest[USART_id].state = Busy;

         /*Save the data of user request*/
         TXRequest[USART_id].buf.data = dataOfBuffer;
         TXRequest[USART_id].buf.size = length;
         TXRequest[USART_id].buf.pos  =  0;
         TXRequest[USART_id].cb       = cb;
      }
      /*Enable Transmitting Register empty interrupt */
      arrOfUARTS[USART_id]->CR1  |=(ENABLE<<TXEIE);

      /*Enable Transmitting Complete interrupt */
      arrOfUARTS[USART_id]->CR1  |=(ENABLE<<TCIE);

      /* Fire the first interrupt by sending the first byte */
      arrOfUARTS[USART_id]->DR =  TXRequest[USART_id].buf.data[ TXRequest[USART_id].buf.pos ++];
      // TXRequest[USART_id].buf.pos ++;  ---> un reachable code


   
      
   }

  return ReturnError;
}
/*****************************************************************************************************************************************/
     
UART_enuErrorStatus USART_receiveBufferAsync(u8 USART_id,u8* dataOfBuffer,u8 length,RX_CB cb ){
   
    UART_enuErrorStatus ReturnError = UART_enumOk;

   /***************************************Validation Part********************************************/
   /*Check on the USART Channel*/
   if(USART_id > USART6){
      ReturnError = UART_enumWrongcConfiguration;

   /*Check on the pointer of Data Buffer*/
   }else if(!dataOfBuffer){
      ReturnError = UART_enumNullPointer;

   /*Check on the Data length*/
    }else if(length > MAX_DATA_LENGTH){
      ReturnError = UART_enumWrongDataLength;

   /************************************Implementation Part********************************************/
   }else{

      if(RXRequest[USART_id].state == Ready)
      {
         RXRequest[USART_id].state = Busy;
         /*Disable interrupt to discard any data on the bus */
         arrOfUARTS[USART_id]->CR1 &=  ~(ENABLE<<RXNEIE);

         /*Save the data of user request*/
         RXRequest[USART_id].buf.data = dataOfBuffer;
         RXRequest[USART_id].buf.pos  = 0;
         RXRequest[USART_id].buf.size = length;
         RXRequest[USART_id].cb = cb;

         /*Enable interrupt to start from here receiving the data on the bus*/
         arrOfUARTS[USART_id]->CR1  |=(ENABLE<<RXNEIE);
      }
   }
   return ReturnError;
}
/*****************************************************************************************************************************************/
UART_enuErrorStatus USART_sendByte(u8 USART_id,u8 byte){
   UART_enuErrorStatus ReturnError = UART_enumOk;

   /***************************************Validation Part********************************************/
   /*Check on the USART Channel*/
   if(USART_id > USART6){
      ReturnError = UART_enumWrongcConfiguration;

   /*Check on the Data Length*/
   }else if(byte > MAX_DATA_LENGTH){
      ReturnError = UART_enumWrongDataLength;

  /************************************Implementation Part********************************************/
   }else{

      u16 volatile timeout = 5000;

      if(TXRequest[USART_id].state == Ready)
      {
         TXRequest[USART_id].state = Busy;

         /*Send a byte*/
         arrOfUARTS[USART_id]->DR = byte;

         /*Polling on the transmit complete flag*/
    
         while (timeout&&((((arrOfUARTS[USART_id]->SR)>>TC)&1) == DISABLE)){
               timeout--;
         }
         /*Check on the transmit complete flag */
         if(((arrOfUARTS[USART_id]->SR)>>TC)&1){
           /*Byte is sent*/
         }else{
            ReturnError = UART_enumWronginTransmission;
         }
         TXRequest[USART_id].state =   Ready;
      }
   }
    return ReturnError;
}
/*****************************************************************************************************************************************/
UART_enuErrorStatus USART_receiveByte(u8 USART_id,u8* byte){
   UART_enuErrorStatus ReturnError = UART_enumOk;

   /***************************************Validation Part********************************************/
   /*Check on the USART Channel*/
   if(USART_id > USART6){
      ReturnError = UART_enumWrongcConfiguration;

   /*Check on Pointer that carries a received value*/   
   }else if(!byte){
      ReturnError = UART_enumNullPointer;

   /************************************Implementation Part********************************************/
   }else{

      if(RXRequest[USART_id].state == Ready)
      {
         RXRequest[USART_id].state = Busy;

         /*Polling on the read data register not empty*/
         u32 volatile timeout = 5000;

         while (timeout&&((((arrOfUARTS[USART1]->SR)>>RXNE)&1) == DISABLE))
         {    
            timeout--;
         }

         /*Check on the read data register not empty*/
         if(((arrOfUARTS[USART1]->SR)>>RXNE)&1){

         /*Receive a byte*/
         *byte = arrOfUARTS[USART_id]->DR;
         }else{
            ReturnError = UART_enumWronginReception;

         }
      RXRequest[USART_id].state =  Ready;
  
      }
   }
 return ReturnError;
}
/*****************************************************************************************************************************************/
/************************************************************************/
/*					          USART Handlers                                 */
/************************************************************************/
void USART1_IRQHandler(void){

   /*Check on Transmission complete flag */
   if(((arrOfUARTS[USART1]->SR)>>TC)&1)
   {
      if((TXRequest[USART1].buf.pos < TXRequest[USART1].buf.size)){

         /*Send one byte*/
         arrOfUARTS[USART1]->DR = TXRequest[USART1].buf.data[TXRequest[USART1].buf.pos];
         TXRequest[USART1].buf.pos++;  
      }
      else
      {
         /*Disable Transmitting interrupt Enable*/
         arrOfUARTS[USART1]->CR1  &=~(ENABLE<<TXEIE);
         /*Disable Transmitting complete Enable*/
          arrOfUARTS[USART1]->CR1  &=~(ENABLE<<TCIE);


         /*Now, The USART is ready to accept a new request*/
         TXRequest[USART1].state = Ready;

         /*Call callback function to notifiy the user that the buffer transmission is done */
         if(TXRequest[USART1].cb){
            TXRequest[USART1].cb();
         }
      }
   }
  /*Check on the read data register not empty */
  if (((arrOfUARTS[USART1]->SR)>>RXNE)&1)
   {
      if(RXRequest[USART1].buf.pos < RXRequest[USART1].buf.size){
         /*Receive one byte*/
         RXRequest[USART1].buf.data[RXRequest[USART1].buf.pos++] =  arrOfUARTS[USART1]->DR;
         
      }else{

         /*Now, The USART is ready to accept a new request*/
         RXRequest[USART1].state = Ready;

         /*Call callback function to notifiy the user that the buffer receiving is done */
         if(RXRequest[USART1].cb){
            RXRequest[USART1].cb();
         }
      }
     
   }  
}

/************************************************************************************************************************************/
void USART2_IRQHandler(void){
   /*Check on the transmit data register empty flag */
   if(((arrOfUARTS[USART2]->SR)>>TXE)&1)
   {
      if(TXRequest[USART2].buf.pos < TXRequest[USART2].buf.size){

         /*Send one byte*/
         arrOfUARTS[USART2]->DR = TXRequest[USART2].buf.data[TXRequest[USART2].buf.pos];
         TXRequest[USART2].buf.pos++;  
      }
      else{

         /*Disable Transmitting interrupt*/
         arrOfUARTS[USART2]->CR1  &=~(ENABLE<<TXEIE);

         /*Now, The USART is ready to accept a new request*/
         TXRequest[USART2].state = Ready;

         /*Call callback function to notifiy the user that the buffer transmission is done */
         if(TXRequest[USART2].cb){
            TXRequest[USART2].cb();
         }
      }
   }
  if (((arrOfUARTS[USART2]->SR)>>RXNE)&1)
   {
      if(RXRequest[USART2].buf.pos < RXRequest[USART2].buf.size){

          /*Receive one byte*/
         RXRequest[USART2].buf.data[RXRequest[USART2].buf.pos] =  arrOfUARTS[USART2]->DR;
         RXRequest[USART2].buf.pos++;

      }else{

         /*Now, The USART is ready to accept a new request*/
         RXRequest[USART1].state = Ready;
         
         /*Call callback function to notifiy the user that the buffer receiving is done */
         if(RXRequest[USART2].cb){
            RXRequest[USART2].cb();
         }
      }
     
   }  
}

/************************************************************************************************************************************/
void USART6_IRQHandler(void){
   if(((arrOfUARTS[USART6]->SR)>>TXE)&1)
   {
      if(TXRequest[USART6].buf.pos < TXRequest[USART6].buf.size){
         /*Send one byte*/
         arrOfUARTS[USART6]->DR = TXRequest[USART6].buf.data[TXRequest[USART6].buf.pos];
         TXRequest[USART6].buf.pos++;  
      }
      else{
         /*Disable Transmitting interrupt*/
         arrOfUARTS[USART6]->CR1  &=~(ENABLE<<TXEIE);

         /*Call callback function to notifiy the user that the buffer transmission is done */
         if(TXRequest[USART6].cb){
            TXRequest[USART6].cb();
         }
      }
   }
  if (((arrOfUARTS[USART6]->SR)>>RXNE)&1)
   {
      if(RXRequest[USART6].buf.pos < RXRequest[USART6].buf.size){

         /*Receive one byte*/
         RXRequest[USART6].buf.data[RXRequest[USART6].buf.pos] =  arrOfUARTS[USART6]->DR;
         RXRequest[USART6].buf.pos++;
      }else{

         /*Now, The USART is ready to accept a new request*/
         RXRequest[USART1].state = Ready;
         
         /*Call callback function to notifiy the user that the buffer receiving is done */
         if(RXRequest[USART6].cb){
            RXRequest[USART6].cb();
         }
      }
     
   }  
}



