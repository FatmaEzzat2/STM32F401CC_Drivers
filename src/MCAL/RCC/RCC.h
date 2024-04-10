/************************************************************************************************************
 *************************            File Name: RCC.h                           ************************
 *************************            Layer	   : MCAL                                ************************
 *************************            Module   : RCC                                 ************************
 *************************            Version  : V 0.0                               ************************
 *************************            Created  : 12/2/2023                            ************************
 *************************            Author   : Fatma Ezzat                     ************************
 *************************Brief: This Header file defines functions for RCC driver************************.
 ************************************************************************************************************/

#ifndef RCC_H_
#define RCC_H_

#include "../../Lib/STD_TYPES.h"
/********************************** 1- Defines **************************************/

/*Enable and Disable Clock Sources*/
#define CLK_HSI		0x00000001
#define CLK_HSE		0x00010000
#define CLK_PLL		0x01000000

/*Clock System Source*/
#define SYS_CLK_HSI     0x00000000
#define SYS_CLK_HSE     0x00000001
#define SYS_CLK_PLL     0x00000002

/*PLL Source*/
#define PLL_HSI   0
#define PLL_HSE   1

/*AHB PreScaler*/
#define SYSCLK_NOT_DIVIDE    0b0000
#define SYSCLK_DIVIDE_2      0b1000
#define SYSCLK_DIVIDE_4		 0b1001
#define SYSCLK_DIVIDE_8		 0b1010
#define SYSCLK_DIVIDE_16	 0b1011
#define SYSCLK_DIVIDE_64	 0b1100
#define SYSCLK_DIVIDE_128    0b1101
#define SYSCLK_DIVIDE_256	 0b1110
#define SYSCLK_DIVIDE_512	 0b1111

/*APB PreScaler*/
#define AHB_NOT_DIVIDE 		0b000
#define AHB_DIVIDE_2		0b100
#define AHB_DIVIDE_4		0b101
#define AHB_DIVIDE_8		0b110
#define AHB_DIVIDE_16		0b111

/********************************** 2- Types ****************************************/
typedef enum{
	RCC_enumOK,
	RCC_enumNOK,
	RCC_enumClockNotReady,
	RCC_enumWrongPLLParameter,
}ErrorState;

/*Peripherals*/
typedef enum{
	GPIOA_EN =0,
	GPIOB_EN,
	GPIOC_EN,
	GPIOD_EN,
	GPIOE_EN,
	GPIOH_EN =7,
	CRC_EN   =12,
	DMA1_EN  =21,
	DMA2_EN  =22
}AHB_Peripheral_t;

typedef enum{
	TIM2_EN =0,
	TIM3_EN,
	TIM4_EN,
	TIM5_EN,
	WWDG_EN =11,
	SPI2_EN =14,
	SPI3_EN,
	USART2_EN=17,
	I2C1_EN=21,
	I2C2_EN,
	I2C3_EN,
	PWR_EN=28,
}APB1_Peripheral_t;

typedef enum{
	TIM1_EN=0,
	USART1_EN=4,
	USART6_EN,
	ADC1_EN=8,
	SDIO_EN=11,
	SPI1_EN,
	SPI4_EN,
	SYSCFG_EN,
	TIM9_EN=16,
	TIM10_EN,
	TIM11_EN
}APB2_Peripheral_t;
/****************************** 3- Function Prototypes ******************************/
/*
 * @brief : Function to Enable any clock source
 * @parameter : Clock Type
 * @return : void
 */
ErrorState RCC_EnableClock(u32 clk);
/*
 * @brief : Function to Disable any clock source
 * @parameter : Clock Type
 * @return : void
 */
void RCC_DisableClock(u32 clk);
/*
 * @brief : Function to Choose the system clock
 * @parameter : Clock Source
 * @return : void
 * */
void RCC_SelectClockSource(u32 sysClk);
/*
 * @brief : Function to Return current system clock
 * @Parameter : void
 * @return : Clock Source
 * */
u8 RCC_GetSystemClock(void);
/*
 * @brief :Function to Configure PLL Parameters
 * @Parameter : PLL Parameters
 * parameter[0] = 2 ≤ PLLM ≤ 63
 * parameter[1] = PLLP = 2,4,6,8
 * parameter[2] = 192 ≤ PLLN ≤ 432
 * parameter[3] =  2 ≤PLLQ ≤15
 * @return: ErrorState
 * PLL Equation = f(PLL clock input) × (PLLN /(PLLM * PLLP))
 */
ErrorState RCC_ConfigurePLL(u32 PLLM,u32 PLLP,u32 PLLN,u32 PLLQ);
/*
 * @brief:Function to Select PLL Source
 * @parameter: PLL Source
 * @return: void
 * */
ErrorState RCC_SelectPLLSource(u8 source);

/*
 * @brief : Function to Configure Pre_scaler of AHB Buses
 * @Parameter :PreScaler
 * @return : void
 * */
void RCC_SelectAHBPrescaler(u32 prescaler);

/*
 * @brief : Function to Configure Pre_scaler of APB1 Bus
 * @Parameter :PreScaler
 * @return : void
 * */
void RCC_SelectAPB1Prescaler(u32 prescaler);

/*
 * @brief : Function to Configure Pre_scaler of APB2 Bus
 * @Parameter :PreScaler
 * @return : void
 * */
void RCC_SelectAPB2Prescaler(u32 prescaler);
/*
 * @brief : Function to Enable AHB Peripheral
 * @Parameter : Peripheral type
 * @return : void
 * */
void RCC_EnableAHBPeripherals(AHB_Peripheral_t peripheral);
/*
 * @brief : Function to Enable APB1 Peripheral
 * @Parameter : Peripheral type
 * @return : void
 * */
void RCC_EnableAPB1Peripherals(APB1_Peripheral_t peripheral);

/*
 * @brief : Function to Enable APB2 Peripheral
 * @Parameter : Peripheral type
 * @return : void
 * */
void RCC_EnableAPB2Peripherals(APB2_Peripheral_t peripheral);
/*
 * @brief : Function to Disable AHB Peripheral
 * @Parameter : Peripheral type
 * @return : void
 * */
void RCC_DisableAHBPeripherals(AHB_Peripheral_t peripheral);
/*
 * @brief : Function to Disable APB1 Peripheral
 * @Parameter : Peripheral type
 * @return : void
 * */
void RCC_DisableAPB1Peripherals(APB1_Peripheral_t peripheral);

/*
 * @brief : Function to Disable APB2 Peripheral
 * @Parameter : Peripheral type
 * @return : void
 * */
void RCC_DisableAPB2Peripherals(APB2_Peripheral_t peripheral);
#endif
