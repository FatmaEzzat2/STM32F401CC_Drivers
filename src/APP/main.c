#include "../MCAL/RCC/RCC.h"
#include "../MCAL/GPIO/GPIO.h"
#include "../MCAL/NVIC/NVIC.h"
#include "../MCAL/SYSTICK/SYSTICK.h"
#include "../HAL/0_LED/LED.h"
#include "../HAL/1_SW/SW.h"

void delay(void){
	for(volatile u32 i=0;i<50000;i++);
}
void ADC_IRQHandler(void){
		LED_SetStatus(LED_2,LED_ON);
		 delay();
		LED_SetStatus(LED_2,LED_OFF);
}
void LED_toggle (void){
	LED_SetStatus(LED_2,LED_ON);
	delay();
	LED_SetStatus(LED_2,LED_OFF);

}
int main(void)
{
	
	
	
	RCC_EnableAHBPeripherals(GPIOA_EN);
	LED_init();

	 SYSTICK_CallBack(LED_toggle);
	 SYSTICK_SetTimeMS(1000);
	SYSTICK_Start(INFINITY);
	 delay();


  while (1)
    {

    }
}
