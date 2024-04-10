/*
*File: HAL Switch
*Author:  Fatma Ezzat
*Created: 3/20/2024
*Target:  STM32F401cc
*/
#include "../APP.h"

#if (APP == HSwitch_APP)
/********************************************************************************************************/
/************************************************Includes************************************************/
/********************************************************************************************************/
#include "../../MCAL/RCC/RCC.h"
#include "../../MCAL/GPIO/GPIO.h"
#include "../../MCAL/SYSTICK/SYSTICK.h"
#include "../../Schedular/Sched.h"
#include "../../HAL/0_LED/LED.h"
#include "../../HAL/1_HSW/HSW.h"



/********************************************************************************************************/
/************************************************Defines*************************************************/
/********************************************************************************************************/

void Toggle_led_3(void){
   static u8 ledState = LED_OFF;
   ledState ^= 1;
    if (ledState == LED_OFF )
    {
       LED_SetStatus(LED_1,LED_OFF);
    }else{
        LED_SetStatus(LED_1,LED_ON);
    }
}
/*Every 50 ms*/
void APP_Runnable(void){
    u8 state =0;
    if(SW_getSwState(Switch_1,&state)==PRESSED){
        Toggle_led_3();
    }
}


int main(void){

    RCC_EnableAHBPeripherals(GPIOA_EN);

    LED_init();
    SW_init();
    Sched_init();
    Sched_Start();
    return 0;
}
#endif

