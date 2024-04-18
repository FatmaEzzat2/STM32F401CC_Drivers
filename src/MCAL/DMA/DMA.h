/*
*File: Header File of DMA
*Author:  Fatma Ezzat
*Created: 13/4/2024
*Target:  STM32F401cc
*/
/********************************************************************************************************/
/************************************************Includes************************************************/
/********************************************************************************************************/
#include "../../Lib/STD_TYPES.h"

/********************************************************************************************************/
/************************************************Defines*************************************************/
/********************************************************************************************************/
/*DMA Options*/
#define     DMA1         0
#define     DMA2         1

/*Stream Options*/
#define    STREAM0      0
#define    STREAM1      1
#define    STREAM2      2
#define    STREAM3      3
#define    STREAM4      4
#define    STREAM5      5
#define    STREAM6      6
#define    STREAM7      7

/*Interrupt Mode*/
#define INT_DISABLE                     0
#define INT_ENABLE                      1

/*Stream Mode*/
#define STREAM_DISABLE                  0
#define STREAM_ENABLE                   1


/*
@brief:DMA is capable of performing three different transfer modes.
*/
/*Data Transfer Direction*/
#define PERIPHERAL_TO_MEMORY            0b00
#define MEMORY_TO_PERIPHERAL            0b01
#define MEMORY_TO_MEMORY                0b10
/*11 is reserved*/

/*Circular Mode*/
#define CIRCULAR_MODE_DISABLE           0
#define CIRCULAR_MODE_ENABLE            1

/*Peripheral(Source) Increment Mode*/
#define  PERIPHERAL_ADDRESS_PTR_FIXED   0
#define  PERIPHERAL_ADDRESS_PTR_INCR    1

/*Memory(Destination) Increment Mode*/
#define  MEMORY_ADDRESS_PTR_FIXED       0
#define  MEMORY_ADDRESS_PTR_INCR        1

/* Peripheral Data Size*/
#define PERIPHERAL_Byte_8BITS           0b00
#define PERIPHERAL_HALF_WORD_16BITS     0b01
#define PERIPHERAL_WORD_32BITS          0b10
/*11 is reserved*/

/*Memory Data Size*/
#define MEMORY_Byte_8BITS               0b00
#define MEMORY_HALF_WORD_16BITS         0b01
#define MEMORY_WORD_32BITS              0b10
/*11 is reserved*/

/*
*@brief: 
Stream priority is software-configurable (there are four software levels).
If two or more DMA streams have the same software priority level, the hardware priority is used 
(stream 0 has priority over stream 1
*/
/*Pariority Levels*/
#define PRIORITY_LOW                    0b00
#define PRIORITY_MEDIUM                 0b01
#define PRIORITY_HIGH                   0b10
#define PRIORITY_VERY_HIGH              0b11

/*Double Buffer Mode*/
#define DOUBLE_BUFFER_DISABLE           0
#define DOUBLE_BUFFER_ENABLE            1

/*Data Direct Mode*/
#define DATA_DIRECT_MODE_DISABLE     1
#define DATA_DIRECT_MODE_ENABLE      0


#define DISABLE     0
#define ENABLE      1

/*Interrupts*/
#define INT_CLR     0x0000001F



/*FIFO Buffer*/
#define _1_4_FULL_FIFO          0b00
#define _1_2_FULL_FIFO          0b01
#define _3_4_FULL_FIFO          0b10
#define FULL_FIFO               0b11


 /*Call Back function to Complete transfer */
 typedef void (*Transfer_completeCB)(void);

/*Call Back function to  Half Complete transfer */
 typedef void (*Half_transferCB)(void);


/********************************************************************************************************/
/************************************************Types***************************************************/
/********************************************************************************************************/
typedef struct 
{
    /*Options: 
    DMA1
    DMA2
    */
    u8 DMA_Num;
    /*Options: 
    Stream_1
    Stream_2
    Stream_3
    Stream_4
    Stream_5
    Stream_6
    Stream_7
    */
    u8 Stream_Num;

    /*Options:
    000: channel 0 selected
    001: channel 1 selected
    010: channel 2 selected
    011: channel 3 selected
    100: channel 4 selected
    101: channel 5 selected
    110: channel 6 selected
    111: channel 7 selected
    */
    u8 Channel_Num;

    /*Options: 
    0: No buffer switching at the end of transfer
    1: Memory target switched at the end of the DMA transfer
    */
    u8 Double_buffer_mode;
    
    /*Options: 
    00: Low
    01: Medium
    10: High
    11: Very high
    */
    u8 Priority_level;

    /*Options: 
    0: Memory address pointer is fixed
    1: Memory address pointer is incremented after each data transfer
    */
    u8  Memory_increment_mode;

    /*Options: 
    0: Peripheral address pointer is fixed
    1: Peripheral address pointer is incremented after each data transfer
    */
    u8  Peripheral_increment_mode;

    /*Options: 
    00: byte (8-bit)
    01: half-word (16-bit)
    10: word (32-bit)
    11: reserved
    */
    u8 Memory_data_size;

    /*Options:
    00: Byte (8-bit)
    01: Half-word (16-bit)
    10: Word (32-bit)
    11: reserved*/
    u8 Peripheral_data_size;

    /*Options: 
    0: Circular mode disabled
    1: Circular mode enabled
    */
    u8 Circular_mode;

    /*Options:
    00: Peripheral-to-memory
    01: Memory-to-peripheral
    10: Memory-to-memory
    11: reserved
     */
    u8 Data_transfer_direction;
    /*Options:
    0:Enable
    1:Disable
    */
    u8 Data_Direct_mode;

    /*Options:
    00: 1/4 full FIFO
    01: 1/2 full FIFO
    10: 3/4 full FIFO
    11: full FIFO
    */
    u8 FIFO_threshold_selection;

    /*Call Back function to Complete transfer */
    Transfer_completeCB CompTransCB;

    /*Call Back function to  Half Complete transfer */
    Half_transferCB   HalfCompTransCB  ;

}StreamConfiguration;

typedef struct
{ 
	u8 Stream;
	u32* Peripheral_Address;
	u32* Memory_0_Address;
	u32* Memory_1_Address;
	u16 Block_Length;

}STREAM_Request;

/*
 *@brief : The Error List Type                                           
*/
typedef enum{
	/*
	 *@brief : Everything Ok, Function had Performed Correctly.
	 */
	DMA_enumOk,          
	/*
	 *@brief : Select Wrong init Configuration
	 */    
	DMA_enumWrongcConfiguration,      
	/*
	 *@brief : Send Null Pointer
     */
    DMA_enumNullPointer
}DMA_enuErrorStatus;


/********************************************************************************************************/
/************************************************APIs****************************************************/
/********************************************************************************************************/
/*
 * @brief Function to initialize a DMA stream.
 * @parameter None
 * @return DMA_enuErrorStatus Indicates the status of the initialization process.
 */
DMA_enuErrorStatus DMA_initStream(void);

/*
 * @brief Sets the address of the source and destination in a single buffer DMA transfer.
 * @parameter DMA_Num The number of the DMA controller.
 *            data Pointer to the structure containing the DMA stream request information.
 * @return DMA_enuErrorStatus Indicates the status of the address setting process.
 * NOTE :
 * We add the Base address of the peripheral data register
 */
DMA_enuErrorStatus DMA_SetAddressInSingleBuffer(u8 DMA_Num, STREAM_Request* data);

/*
 * @brief Sets the address of the source and destination in a double buffer DMA transfer.
 * @parameter DMA_Num The number of the DMA controller.
 *            data Pointer to the structure containing the DMA stream request information.
 * @return DMA_enuErrorStatus Indicates the status of the address setting process.
 * NOTE :
 * We add the Base address of the peripheral data register
 */
DMA_enuErrorStatus DMA_SetAddressInDoubleBuffer(u8 DMA_NUM, STREAM_Request* data);

/*
 * @brief Registers callback functions for DMA interrupt events.
 * @parameter tcCB Pointer to the transfer complete callback function.
 *            htcCB Pointer to the half transfer complete callback function.
 * @return DMA_enuErrorStatus Indicates the status of the callback registration process.
 */
DMA_enuErrorStatus DMA_GetInterruptCBFunc(Transfer_completeCB tcCB, Half_transferCB htcCB);

/*
 * @brief Enables a specific DMA stream.
 * @parameter DMA_NUM The number of the DMA controller.
 *            stream The stream number to be enabled.
 * @return DMA_enuErrorStatus Indicates the status of the enabling process.
 */
DMA_enuErrorStatus DMA_Enable(u8 DMA_NUM,u8 stream);

