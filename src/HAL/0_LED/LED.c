/************************************************************************************************************
 *************************            File Name: LED.c                          ************************
 *************************            Layer	   : HAL                            ************************
 *************************            Module   : LED                            ************************
 *************************            Version  : V 0.0                           ************************
 *************************            Created  : 18/2/2023                       ************************
 *************************            Author   : Fatma Ezzat                     ************************
 ****Brief: This Source file defines the implementations of functions for LED driver**.
 ************************************************************************************************************/

/*************************** Includes  **********************************/
#include"LED.h"
#include "../../MCAL/GPIO/GPIO.h"

/*************************** Variables **********************************/

extern  const LED_confg_t arrayOfLeds[_NUM_OF_LEDS];

/*************************** Implementation  ****************************/
void LED_init(void){

	GPIO_PIN_CONFG led;

	/*Speed & Mode of pins are common between all pins*/
	led.speed = SPEED_MEDIUM;
	led.mode  = GPIO_GP_OUTPUT_PUSHPULL_PULL_UP;

	/*For every pin*/
	for(u8 LED_index=0;LED_index<_NUM_OF_LEDS;LED_index++){

		led.port = arrayOfLeds[LED_index].port;
		led.pin  = arrayOfLeds[LED_index].pin;
		GPIO_InitPin(&led);
	}
}

void LED_SetStatus(u32 led,u32 status){
	 GPIO_SetPinValue(arrayOfLeds[led].port,arrayOfLeds[led].pin,(status)^(arrayOfLeds[led].connection));
}
