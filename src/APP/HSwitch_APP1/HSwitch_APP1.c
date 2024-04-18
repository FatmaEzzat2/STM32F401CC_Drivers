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


//  u8 gledState = LED_OFF;
// u8 yledState = LED_OFF;
// /*Every 50 ms*/

// void APP_Runnable1(void){
//     u8 state =0;
    
//     SW_getSwState(Switch_1,&state);
//     if(state==PRESSED){
//        gledState ^= 1;
//         if (gledState == LED_OFF )
//         {
//             LED_SetStatus(LED_g,LED_OFF);
//         }else{
//             LED_SetStatus(LED_g,LED_ON);
//         }
//     }
// }

// void APP_Runnable2(void){
//     u8 state =0;
    
//     SW_getSwState(Switch_2,&state);
//     if(state==PRESSED){
//        yledState ^= 1;
//     if (yledState == LED_OFF )
//     {
//        LED_SetStatus(LED_y,LED_OFF);
//     }else{
//         LED_SetStatus(LED_y,LED_ON);
//     }
//     }
// }
int main(void){
    	GPIO_PIN_CONFG TX;
	GPIO_PIN_CONFG RX;

	/** output push pull */
	/** Alternative 7 */
	// TX.GPIO_AT_Type = GPIO_AT_PushPull;
	// TX.GPIO_Mode    = GPIO_MODE_AF7;
	TX.pin	    = PIN_9;
	TX.port		= PORT_A;
	TX.speed	= SPEED_MEDIUM;
    TX.mode     = GPIO_AF_OUTPUT_PUSHPULL_PULL_UP;

    
	/** input pulldown */
	/** Alternative 7 */
	// RX.GPIO_AT_Type = GPIO_AT_PullDown;
	// RX.GPIO_Mode    = GPIO_MODE_AF7;
	RX.pin	    = PIN_10;
	RX.port		= PORT_A;
	RX.speed	= SPEED_MEDIUM;
	//RX.mode     = GPIO_ALTERNATIVE_FUNC;
	GPIO_InitPin(&TX);
	GPIO_InitPin(&RX);
    
    //GPIO_CFG_AlternativeFunction(PORT_A,PIN_9,GPIO_AF07);
   // GPIO_CFG_AlternativeFunction(PORT_A,PIN_10,GPIO_AF07);

    // RCC_EnableAHBPeripherals(GPIOA_EN);
    // RCC_EnableAHBPeripherals(GPIOB_EN);
    // LED_init();
    // SW_init();
    // Sched_init();
    // Sched_Start();
    return 0;
}
#endif

