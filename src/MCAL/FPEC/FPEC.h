#ifndef MCAL_FPEC_FPIC_H_
#define MCAL_FPEC_FPIC_H_
/********************************************************************************************************/
/************************************************Includes************************************************/
/********************************************************************************************************/
#include "../../Lib/STD_TYPES.h"

/********************************************************************************************************/
/************************************************Defines*************************************************/
/********************************************************************************************************/
/*
Sectors:
Sector 0    0x0800 0000 - 0x0800 3FFF    16 Kbytes
Sector 1    0x0800 4000 - 0x0800 7FFF    16 Kbytes
Sector 2    0x0800 8000 - 0x0800 BFFF    16 Kbytes
Sector 3    0x0800 C000 - 0x0800 FFFF    16 Kbytes
Sector 4    0x0801 0000 - 0x0801 FFFF    64 Kbytes
Sector 5    0x0802 0000 - 0x0803 FFFF    128 Kbytes
Sector 6    0x0804 0000 - 0x0805 FFFF    128 Kbytes
Sector 7    0x0806 0000 - 0x0807 FFFF    128 Kbytes
System mem  0x1FFF 0000 - 0x1FFF 77FF    30 Kbytes
OTP area    0x1FFF 7800 - 0x1FFF 7A0F    528 bytes
Option bytes 0x1FFF C000 - 0x1FFF C00F   16 bytes
*/
#define SECTOR_0        0
#define SECTOR_1        1
#define SECTOR_2        2
#define SECTOR_3        3
#define SECTOR_4        4
#define SECTOR_5        5
#define SECTOR_6        6
#define SECTOR_7        7
#define OTP_Area        8

/*Program Page Size*/
/* Program size
These bits select the program parallelism.
00 program x8
01 program x16
10 program x32
11 program x64
*/
#define PROGRAM_8            0b00
#define PROGRAM_16           0b01
#define PROGRAM_32           0b10
#define PROGRAM_64           0b11

#define ENABLE      1
#define DISABLE     0
/********************************************************************************************************/
/************************************************Types***************************************************/
/********************************************************************************************************/



/********************************************************************************************************/
/************************************************APIs****************************************************/
/********************************************************************************************************/
/*
*@brief : Function to 
*@parameter:
*@return:
*/

void FPEC_voidEraseAppArea(void);
	
void FPEC_voidFlashSectorErase(u8 Copy_u8SectorNumber);

void FPEC_voidFlashWrite(u32 Copy_u32MemoryAddress, u64* Copy_u16Data, u8 Copy_u8PageSize);

#endif // MCAL_FPEC_FPIC_H_