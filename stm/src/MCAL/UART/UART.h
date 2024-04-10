/*
*File: Header File  of UART
*Author:  Fatma Ezzat
*Created: 4/7/2024
*Target:  STM32F401cc
*/
#ifndef MCAL_UART_UART_H_
#define MCAL_UART_UART_H_

/********************************************************************************************************/
/************************************************Includes************************************************/
/********************************************************************************************************/
#include"../../Lib/STD_TYPES.h"

/********************************************************************************************************/
/************************************************Defines*************************************************/
/********************************************************************************************************/
/* Oversampling Mode*/
#define OVER_SAMPLING_BY_16     0
#define OVER_SAMPLING_BY_8      1

/* USART Enable*/
#define USART_DISABLE           0
#define USART_ENABLE            1

/* Word Length*/
#define DATA_BITS_8             0
#define DATA_BITS_9             1

/*Parity Control Enable*/
#define PARTY_DISABLE           0b00000000
#define PARTY_ENABLE_EVEN       0b00000010    
#define PARTY_ENABLE_ODD        0b00000011    

/*Stop Bits*/
#define STOP_BIT_1              0b00000000
#define STOP_BIT_1_2            0b00000001
#define STOP_BIT_2              0b00000010
#define STOP_BIT_3_2            0b00000011


/*USART Types*/
#define USART1          0
#define USART2          1
#define USART6          2
/*
#define F_USART1         16000000
#define F_USART2         16000000
#define F_USART6         16000000
*/
/********************************************************************************************************/
/************************************************Types***************************************************/
/********************************************************************************************************/
#define DISABLE     0
#define ENABLE      1



typedef struct{
    /*Options:
    1-USART1
    2-USART2
    3-USART6
    */
    u8 Channel;
   
    /*Options: 
    0: oversampling by 16
    1: oversampling by 8
    */
    u8 Oversampling_mode;
   
    /*Options:
    0: 1 Start bit, 8 Data bits, n Stop bit
    1: 1 Start bit, 9 Data bits, n Stop bit
    */
    u8 Word_length;
   
    /*Options:
    00:PARTY_DISABLE          
    01:PARTY_ENABLE_EVEN         
    11:PARTY_ENABLE_ODD          
    */
    u8 ParityControl;
   
    /*Options:
    00: 1 Stop bit
    01: 0.5 Stop bit
    10: 2 Stop bits
    11: 1.5 Stop bit
   */ 
    u8 StopBits;
  
    f32 BaudRate;

    u32 frequncy;

}USART_initialize;


/*USART State*/
typedef enum {

    Ready,
    Busy
}RequestState;


/*Callback function data types for TX & RX*/
typedef void (*TX_CB)(void);
typedef void (*RX_CB)(void);

/*Buffer content*/
typedef struct {

    /*Pointer to the start of the buffer*/
    u8* data;    
    /*The curent position of the byte in the buffer*/   
    u32 pos;      
    /*Total Size of the buffer (in bytes) */
    u32 size;  
}buffer_t;

/*Transmitter Request*/
typedef struct 
{
    /*Transmitted buffer*/
    buffer_t buf;
    /*Current state of the USART*/   
    u8 state;
    /* Indication of transmission operation completion */
    TX_CB cb;
}TX_Req;

/*Receiver Request*/
typedef struct 
{   
    /*Received buffer*/
    buffer_t buf;
    /*Current state of the USART*/  
    u8 state ;
    /* Indication of Reception operation completion */
    RX_CB cb;
   
}RX_Req;



/*
 *@brief : The Error List Type                                           
*/
typedef enum{
	/*
	 *@brief : Everything Ok, Function had Performed Correctly.
	 */
	UART_enumOk,
	/*
	 *@brief : Everything NOT Ok, Function had Performed InCorrectly.
	 */
	UART_enumNOk,             
	/*
	 *@brief : Select Wrong init Configuration
	 */    
	UART_enumWrongcConfiguration,      
	/*
	 *@brief : Send Null Pointer
     */
    UART_enumNullPointer,
    /*
	 *@brief : Send Wrong data length
     */
    UART_enumWrongDataLength,
    /*
	*@brief : An error in Transmission
    */
    UART_enumWronginTransmission,
    /*
	*@brief : An error in Reception
    */
    UART_enumWronginReception
}UART_enuErrorStatus;

/********************************************************************************************************/
/************************************************APIs****************************************************/
/********************************************************************************************************/
/*
 * @brief Initializes the USART module.
 *
 * @param USART_id The ID of the USART module to initialize.
 * @return ErrorState Indicates whether the initialization was successful or encountered an error.
 */

UART_enuErrorStatus USART_init(USART_initialize *init);
/*
 * @brief Sends a byte via USART.
 *
 * @param USART_id The ID of the USART module to use.
 * @param byte The byte to be sent.
 * @return ErrorState Indicates whether the operation was successful or encountered an error.
 */
UART_enuErrorStatus USART_sendByte(u8 USART_id,u8 byte);

/*
 * @brief Sends a buffer of data asynchronously using zero-copy technique via USART.
 *
 * @param USART_id The ID of the USART module to use.
 * @param dataOfBuffer Pointer to the buffer containing the data to be sent.
 * @param length The length of the data buffer.
 * @param cb Callback function to be executed when transmission is complete or encounters an error.
 * @return ErrorState Indicates whether the operation was successful or encountered an error.
 */
UART_enuErrorStatus USART_sendBufferAsyncZeroCopy(u8 USART_id,u8* dataOfBuffer,u8 length, TX_CB cb);

/*
 * @brief Receives a byte asynchronously via USART.
 *
 * @param USART_id The ID of the USART module to use.
 * @param byte Pointer to where the received byte will be stored.
 * @return ErrorState Indicates whether the operation was successful or encountered an error.
 */
UART_enuErrorStatus USART_receiveByte(u8 USART_id,u8 *byte);

/*
 * @brief Receives a buffer of data asynchronously via USART.
 *
 * @param USART_id The ID of the USART module to use.
 * @param dataOfBuffer Pointer to the buffer where the received data will be stored.
 * @param length The length of the data buffer.
 * @param cb Callback function to be executed when reception is complete or encounters an error.
 * @return ErrorState Indicates whether the operation was successful or encountered an error.
 */
UART_enuErrorStatus USART_receiveBufferAsync(u8 USART_id,u8* dataOfBuffer,u8 length,RX_CB cb );



#endif // MCAL_UART_UART_H_