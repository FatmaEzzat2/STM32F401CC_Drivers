/*
*File: Sched_Confg.c
*Author:  Fatma Ezzat
*Created: 19/3/2024
*Target:  STM32F401cc
*/
#include "Sched.h"
#include "../APP/APP_Runnables.h"



const User_RInfo UsrRInfo[_MAX]={
   /*
    [SW_Runnable]={
        .name="SW_Runnable",
        .periodicity=5,
        .firstDelay=0,
        .cb=HSW_Runnable,
    },
    [APP_runnable]={
        .name="APP_Runnable",
        .periodicity=100,
        .firstDelay=0,
        .cb=APP_Runnable,
    }*/
    /*[Traffic_light]={
        .name ="Traffic",
        .periodicity =2000,
        .firstDelay =0,
        .cb = TrafficLight_Runnable
    } */
    [LCD_TASK]={
        .name ="LCD_TASK",
        .periodicity =2,
        .firstDelay =0,
        .cb = LCD_Task_Runnable
    },
    [LCD_APP]={
        .name ="LCD_TASK",
        .periodicity =2000,
        .firstDelay =1000,
        .cb = LCD_APP_Runnable
    }
    
};