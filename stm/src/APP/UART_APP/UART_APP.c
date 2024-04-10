/*
*File: 
*Author:  Fatma Ezzat
*Created:
*Target:  STM32F401cc
*/

#include "../APP.h"

#if (APP == UART_APP)
#include "../../MCAL/RCC/RCC.h"
#include "../../MCAL/GPIO/GPIO.h"
#include "../../MCAL/NVIC/NVIC.h"
#include "../../MCAL/UART/UART.h"
#include "../../HAL/0_LED/LED.h"
#include "../../HAL/0_LED/LED_Confg.h"
extern USART_initialize UART1_init ;

// test USART_receiveBufferAsync
u8 buffer1[3];
void Toggle_Led_1(void){
    if((buffer1[0]=='f')&&(buffer1[1]=='l')&&(buffer1[2]=='k')){
        LED_SetStatus(LED_g,LED_ON);
    }       
}

int main(void){

    RCC_EnableAHBPeripherals(GPIOA_EN);
    RCC_EnableAHBPeripherals(GPIOB_EN);
    RCC_EnableAPB2Peripherals(USART1_EN);
    NVIC_EnableInterrupt(NVIC_USART1_INTERRUPT);

    GPIO_PIN_CONFG TX;
	GPIO_PIN_CONFG RX;

	TX.pin	    = PIN_9;
	TX.port		= PORT_A;
	TX.speed	= SPEED_HIGH;
	TX.mode     = GPIO_ALTERNATIVE_FUNC;
	RX.pin	    = PIN_10;
	RX.port		= PORT_A;
	RX.speed	= SPEED_HIGH;
	RX.mode     = GPIO_ALTERNATIVE_FUNC;

	GPIO_CFG_AlternativeFunction(PORT_A,PIN_9,GPIO_AF07);
    GPIO_CFG_AlternativeFunction(PORT_A,PIN_10,GPIO_AF07);
	
	GPIO_InitPin(&TX);
	GPIO_InitPin(&RX);
    LED_init();
    USART_init(&UART1_init);

   u8 buffer2[8]={'m','S','S','N','B','L','D','Y'};
   USART_sendBufferAsyncZeroCopy(USART1,buffer2,8,NULL);
   
    
    u8 byte ;
    
    USART_receiveBufferAsync(USART1,buffer1,3,Toggle_Led_1);

    while (1)
    {   
        // //test USART_receiveByte function
        // USART_receiveByte(USART1,&byte);

        // if(byte == 'm'){
        //      LED_SetStatus(LED_g,LED_ON);
        // }else{
        //     LED_SetStatus(LED_g,LED_OFF);
        // }   

        // USART_sendByte(USART1,'F');
        // USART_sendByte(USART1,'A');
        // USART_sendByte(USART1,'T');
        // USART_sendByte(USART1,'M');
        // USART_sendByte(USART1,'A');
        // USART_sendByte(USART1,'\n');


      

    }
    return 0;
}



#endif