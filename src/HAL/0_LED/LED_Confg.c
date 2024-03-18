/************************************************************************************************************
 *************************            File Name: LED_Confg.c                          ************************
 *************************            Layer	   : HAL                            ************************
 *************************            Module   : LED                            ************************
 *************************            Version  : V 0.0                           ************************
 *************************            Created  : 18/2/2023                       ************************
 *************************            Author   : Fatma Ezzat                     ************************
 ****Brief: This Source file defines the structure of data type of LEDs for LED driver**.
 ************************************************************************************************************/
#include"LED.h"
#include"../../MCAL/GPIO/GPIO.h"


const LED_confg_t arrayOfLeds[_NUM_OF_LEDS]=
{

		[LED_2]={
			.port= PORT_A,
			.pin = PIN_1,
			.connection = FORWARD,
		},
};
