/*
*File: 
*Author:  Fatma Ezzat
*Created:
*Target:  STM32F401cc
*/

#ifndef MCAL_DMA_DMA_VALIDATION_H_
#define MCAL_DMA_DMA_VALIDATION_H_
/************************************************************************/
/*					         Interrupt Status Register                  */
/************************************************************************/
/*Transfer complete interrupt flag*/
#define TCIF            5
/*Half Transfer complete interrupt flag*/
#define HTIF            4
/* Transfer error interrupt flag*/
#define TEIF            3
/* Direct mode error interrupt flag*/
#define DMEIF           2
/*FIFO error interrupt flag*/
#define  FEIFx          0 

/*1 is reserved*/

/************************************************************************/
/*				         Interrupt Flag Clear Register                  */
/************************************************************************/
/*Clear Transfer complete interrupt flag*/
#define CTCIF0           5  
/*Clear Half Transfer complete interrupt flag*/
#define CHTIF0           4
/*Clear Transfer error interrupt flag*/
#define CTEIF0           3
/*Clear Direct mode error interrupt flag*/
#define CDMEIF0          2
/*Clear FIFO error interrupt flag*/
#define CFEIF0           0   

/*1 is reserved*/

/************************************************************************/
/*				           Configuration register                        */
/************************************************************************/
/* Channel selection*/
#define CHSEL               25
/*Memory burst transfer*/
#define  MBURST             23
/*Peripheral burst transfer */
#define  PBURST             21
/*Current target*/
#define CT                  19
/*Double buffer mode*/
#define DBM                 18
/*Priority level*/
#define PL                  16
/*Peripheral increment offset size*/
#define PINCOS              15
/*Memory data size*/
#define MSIZE               13
/*Peripheral data size*/
#define PSIZE               11
/*Memory increment mode*/
#define MINC                10
/*Peripheral increment mode*/
#define PINC                9
/*Circular mode*/
#define CIRC                8
/*Data transfer direction*/
#define DIR                 6
/*Peripheral flow controller*/
#define PFCTRL              5
/*Transfer complete interrupt enable*/
#define TCIE                4
/*Half transfer interrupt enable*/
#define HTIE                3
/*Transfer error interrupt enable*/
#define TEIE                2
/*Direct mode error interrupt enable*/
#define DMEIE               1
/* Stream enable*/
#define EN                  0

/*20, 28, 29, 30 and 31 are reserved*/


/************************************************************************/
/*				           FIFO control register                       */
/************************************************************************/
/*FIFO error interrupt enable*/
#define FEIE        7
/*FIFO status*/
#define FS          3
/*Direct mode disable*/
#define DMDIS       2
/*FIFO threshold selection*/
#define FTH         0

#endif // MCAL_DMA_DMA_VALIDATION_H_