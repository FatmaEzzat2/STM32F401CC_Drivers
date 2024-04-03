#include "APP.h"

#ifndef APP_APP_RUNNABLES_H_
#define APP_APP_RUNNABLES_H_


#if (APP == Schedular_APP)

void Toggle_led_1(void);
void Toggle_led_2(void);

#elif (APP == HSwitch_APP)

void HSW_Runnable(void);
void APP_Runnable(void);

#elif (APP == TrafficLight_APP)
void TrafficLight_Runnable(void);

#elif (APP == LCD_TASK_APP)
void LCD_Task_Runnable(void);
void LCD_APP_Runnable(void);
#endif

#endif // APP_APP_RUNNABLES_H_
