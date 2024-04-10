/*
*File: 
*Author:  Fatma Ezzat
*Created:
*Target:  STM32F401cc
*/

#include "UART.h"

USART_initialize UART1_init  = {
    .Channel = USART1 ,
    .ParityControl = PARTY_DISABLE,
    .StopBits = STOP_BIT_1,
    .Word_length =DATA_BITS_8,
    .BaudRate =9600,
    .frequncy=16000000,
    .Oversampling_mode=OVER_SAMPLING_BY_16,
    

};