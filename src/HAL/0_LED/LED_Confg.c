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

		[LED_g]={
			.port= PORT_B,
			.pin = PIN_0,
			.connection = FORWARD,
		},
		[LED_y]={
			.port= PORT_B,
			.pin = PIN_1,
			.connection = FORWARD,
		},
		[LED_r]={
			.port= PORT_B,
			.pin = PIN_2,
			.connection = FORWARD,
		}
};
