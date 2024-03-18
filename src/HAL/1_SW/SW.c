/************************************************************************************************************
 *************************            File Name: SW.h                              ************************
 *************************            Layer	   : HAL                               ************************
 *************************            Module   : SWITCH                            ************************
 *************************            Version  : V 0.0                             ************************
 *************************            Created  : 18/2/2023                         ************************
 *************************            Author   : Fatma Ezzat                       ************************
 *************************Brief: This Header file defines functions for Switch driver*******************.
 ************************************************************************************************************/
#include"SW.h"
#include"../../MCAL/GPIO/GPIO.h"


extern SW_CONFG_t arrayOfSw[_SW_NUM];
/*
 * @brief: A Function to initialize a switch
 * @parameter: void
 * @return :Error State
 * */
SW_ErrorState SW_init(void){

	SW_ErrorState returnError = SW_enumNOK;


	GPIO_PIN_CONFG sw;
	sw.speed = SPEED_MEDIUM;

	for(u8 sw_index=0; sw_index<_SW_NUM; sw_index++){

		sw.port = arrayOfSw[sw_index].port;
		sw.pin  = arrayOfSw[sw_index].pin;
		sw.mode = arrayOfSw[sw_index].connection;
		GPIO_InitPin(&sw);
	}
	return returnError;
}

/*
 * @brief: A Function to get the state of switch --> Pressed or Not Pressed
 * @parameter: The pin number of switch within a specific port
 * @return :Error State
 * */
SW_ErrorState SW_getSwState(SWs_t switchName,u8* switchState){
	SW_ErrorState returnError = SW_enumNOK;
	u8 swState;

	GPIO_GetPinValue(arrayOfSw[switchName].port,
								   arrayOfSw[switchName].pin,
								   &swState);

	*switchState = swState;
	return returnError;

}

