/************************************************************************************************************
 *************************            File Name: LED.h                          ************************
 *************************            Layer	   : HAL                            ************************
 *************************            Module   : LED                            ************************
 *************************            Version  : V 0.0                           ************************
 *************************            Created  : 18/2/2023                       ************************
 *************************            Author   : Fatma Ezzat                     ************************
 ****Brief: This Header file defines functions for LED driver**.
 ************************************************************************************************************/

#ifndef HAL_0_LED_LED_H_
#define HAL_0_LED_LED_H_

#include"../../Lib/STD_TYPES.h"
#include "LED_Confg.h"

/********************************** 1- Defines **************************************/
/*Connection Options*/
#define REVERSE 	1
#define FORWARD 	0

/*LED State*/
#define LED_ON		1
#define LED_OFF		0

/********************************** 2- Types ****************************************/

typedef struct{
	u8 port;
	u8 pin;
	u8 connection;
}LED_confg_t;

/****************************** 3- Function Prototypes ******************************/

void LED_init(void);
void LED_SetStatus(u32 led,u32 status);


#endif /* HAL_0_LED_LED_H_ */
