/*
*File: HAL Switch
*Author:  Fatma Ezzat
*Created: 3/20/2024
*Target:  STM32F401cc
*/
#include "../APP.h"

#if (APP == TrafficLight_APP)
/********************************************************************************************************/
/************************************************Includes************************************************/
/********************************************************************************************************/
#include "../../MCAL/RCC/RCC.h"
#include "../../MCAL/GPIO/GPIO.h"
#include "../../MCAL/SYSTICK/SYSTICK.h"
#include "../../Schedular/Sched.h"
#include "../../HAL/0_LED/LED.h"


#define PERIODIC_TIME       2

#define GREEN_TO_YELLOW    (6)
#define YELLOW_TO_GREEN    (2)
#define YELLOW_TO_RED      (2)
#define RED_TO_YELLOW      (10)

typedef enum {
    Green,
    Yellow,
    Red
}States_t;

void TrafficLight_Runnable(void){

    static u8 sec = 0;
    static States_t previousState =Yellow;
    static States_t NextState = Green;
    sec += PERIODIC_TIME;
    switch (NextState)
    {
    case Green:
    /*Action*/
    LED_SetStatus(Green_LED,LED_ON);
    LED_SetStatus(Yellow_LED,LED_OFF);
    LED_SetStatus(Red_LED,LED_OFF);
    /*Transition*/
    if (sec == GREEN_TO_YELLOW)
    {
         sec = 0;
         previousState= Green;
         NextState = Yellow;
    }
        break;

    case Yellow:
    /*Action*/
    LED_SetStatus(Green_LED,LED_OFF);
    LED_SetStatus(Yellow_LED,LED_ON);
    LED_SetStatus(Red_LED,LED_OFF);
    /*Transition*/
    if ((sec == YELLOW_TO_RED)&&(previousState == Green))
    {
        sec =0;
        previousState= Yellow;
        NextState = Red;
    }else if((sec ==YELLOW_TO_GREEN)&&(previousState == Red)){
        sec =0;
        previousState= Yellow;
        NextState = Green;
    }
        break;
    case Red:
    /*Action*/
    LED_SetStatus(Green_LED,LED_OFF);
    LED_SetStatus(Yellow_LED,LED_OFF);
    LED_SetStatus(Red_LED,LED_ON);
    /*Transition*/
    if (sec ==RED_TO_YELLOW)
    {
        sec = 0;
        previousState= Red;
        NextState = Yellow;
    }
        break;

 
    default:
        break;
    }

}

int main(void){

    RCC_EnableAHBPeripherals(GPIOA_EN);
    LED_init();
    Sched_init();
    Sched_Start();
    return 0;
}


#endif