/*
*File: 
*Author:  Fatma Ezzat
*Created:
*Target:  STM32F401cc
*/
#include "../APP.h"

#if (APP == DMA_APP)
#include "../../MCAL/RCC/RCC.h"
#include "../../MCAL/SYSTICK/SYSTICK.h"
#include "../../MCAL/NVIC/NVIC.h"
#include "../../MCAL/DMA_2/DMA.h"
#include "../../HAL/0_LED/LED.h"
#include "../../HAL/0_LED/LED_Confg.h"


void TurnON_Led_1(void){

    LED_SetStatus(LED_g,LED_ON);

}
void TurnON_Led_2(void){

     LED_SetStatus(LED_r,LED_ON);
}

   u32 SRC_array [10] = {1,2,3,4,5,6,7,8,9,10};
    u32 DST_array [10] = {0};

int main(){
    
    RCC_EnableAHBPeripherals(DMA2_EN);
    RCC_EnableAHBPeripherals(GPIOB_EN);
    NVIC_EnableInterrupt(NVIC_DMA2_STREAM0_INTERRUPT);
    LED_init();
    DMA_GetInterruptCBFunc(TurnON_Led_1,TurnON_Led_2);
    STREAM_Request dataTransfer={
        .Stream = 0,
        .Peripheral_Address = SRC_array,
        .Memory_0_Address =DST_array,
        .Block_Length =10,
        
        
    };
    DMA_initStream();
    DMA_SetAddressInSingleBuffer(DMA2,&dataTransfer);
    DMA_Enable(DMA2,STREAM0);

    while (1)
    {
        /* code */
    }
    
}



#endif