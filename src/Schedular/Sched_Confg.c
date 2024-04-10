/*
*File: Sched_Confg.c
*Author:  Fatma Ezzat
*Created: 19/3/2024
*Target:  STM32F401cc
*/
#include "Sched.h"

 void APP_Runnable(void);
 void HSW_Runnable(void);



const User_RInfo UsrRInfo[_MAX]={
   
    [SW_Runnable]={
        .name="SW_Runnable",
        .periodicity=5,
        .firstDelay=0,
        .cb=HSW_Runnable,
    },
    [APP_runnable]={
        .name="APP_Runnable",
        .periodicity=50,
        .firstDelay=0,
        .cb=APP_Runnable,
    }
};