/*
*File: LCD With Schedular
*Author:  Fatma Ezzat
*Created: 2/4/2024
*Target:  STM32F401cc
*/
#include "../APP.h"

#if (APP == LCD_TASK_APP)
/********************************************************************************************************/
/************************************************Includes************************************************/
/********************************************************************************************************/
#include "../../MCAL/RCC/RCC.h"
#include "../../MCAL/GPIO/GPIO.h"
#include "../../MCAL/SYSTICK/SYSTICK.h"
#include "../../Schedular/Sched.h"
#include "../../HAL/0_LED/LED.h"
#include "../../HAL/0_LED/LED.h"
#include "../../HAL/2_LCD/LCD.h"

#define SET_POS   1
#define WAIT1     2
#define WRITE     3
#define WAIT2     4
#define CLEAR     5
#define WAIT3     6


void Toggle_Led_1(void){
   static u8 ledState = LED_OFF;
   ledState ^= 1;
    if (ledState == LED_OFF )
    {
       LED_SetStatus(LED_g,LED_OFF);
    }else{
        LED_SetStatus(LED_g,LED_ON);
    }
}
void Toggle_Led_2(void){
   static u8 ledState = LED_OFF;
   ledState ^= 1;
    if (ledState == LED_OFF )
    {
       LED_SetStatus(LED_y,LED_OFF);
    }else{
        LED_SetStatus(LED_y,LED_ON);
    }
}
void Toggle_Led_3(void){
   static u8 ledState = LED_OFF;
   ledState ^= 1;
    if (ledState == LED_OFF )
    {
       LED_SetStatus(LED_r,LED_OFF);
    }else{
        LED_SetStatus(LED_r,LED_ON);
    }
}




void LCD_APP_Runnable(void)
{
    static u8 counter =0;
    counter++;
    if (counter==1)
    {
        LCD_writeStringAsync("Hello: ",6,Toggle_Led_2);
    }else{

        if(counter==2){
        LCD_setCursorPosAsync(FIRST_LINE,9,Toggle_Led_3);
        }
         else if (counter==3)
        {
             LCD_writeStringAsync("123",3,Toggle_Led_3);
        } 
        else if (counter==4)
        {
            LCD_sendCommand(LCD_DISPLAY_ON_CURSOR_ON_BLINK_ON);
        } else if (counter==5){
                LCD_sendCommand(LCD_DISPLAY_ON_CURSOR_ON_BLINK_ON);
    }  
    }

     
     
    
    
}

int main(void){

    RCC_EnableAHBPeripherals(GPIOA_EN);
    RCC_EnableAHBPeripherals(GPIOB_EN);
    LED_init();
    LCD_initAsync(Toggle_Led_1);
  

     Sched_init();
    Sched_Start();



    return 0;
}





#endif