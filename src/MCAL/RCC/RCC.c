/************************************************************************************************************
 *************************            File Name: RCC.c                           ************************
 *************************            Layer	   : MCAL                                ************************
 *************************            Module   : RCC                                 ************************
 *************************            Version  : V 0.0                               ************************
 ***************
 **********            Created  : 12/2/2023                            ************************
 *************************            Author   : Fatma Ezzat                     ************************
 *************************Brief: This source file defines the implementations of functions for RCC driver************************.
 ************************************************************************************************************/
/*************************** 1- Includes  **********************************/
#include"RCC.h"
/*************************** 2- Defines   **********************************/
#define RCC_BaseAddress  0x40023800

#define SYSCLK_MASK	    0x00000003

#define HSI_READYFLAG  	0x00000002
#define HSE_READYFLAG  	0x00020000
#define PLL_READYFLAG  	0x02000000

#define NOTREADY    0
#define READY       1

#define DISABLE     0
#define ENABLE      1

/*PLL Configuration*/
#define PLL_SOURCE     22

#define PLL_M_BITS     0
#define PLL_P_BITS     16
#define PLL_N_BITS 	   6
#define PLL_Q_BITS     24

#define PLL_M_MASK   0xffffffc0
#define PLL_P_MASK   0xfffcffff
#define PLL_Q_MASK   0xf0ffffff
#define PLL_N_MASK   0xffff803f

/*PreScaler*/
#define AHB_CLEAR_MASK   0xffffff0f
#define APB1_CLEAR_MASK  0xffffe3ff
#define APB2_CLEAR_MASK  0xffff1fff

#define AHB_BITS        4
#define APB1_BITS		10
#define APB2_BITS		13

/*************************** 3- Types     **********************************/
typedef struct{
	u32 CR;
	u32 PLLCFGR;
	u32 CFGR;
	u32 CIR ;
	u32 AHB1RSTR;
	u32 AHB2RSTR;
	u32 Reserved_0[2];
	u32 APB1RSTR;
	u32 APB2RSTR;
	u32 Reserved_1[2];
	u32 AHB1ENR;
	u32 AHB2ENR;
	u32 Reserved_2[2];
	u32 APB1ENR;
	u32 APB2ENR;
	u32 Reserved_3[2];
	u32 AHB1LPENR;
	u32 AHB2LPENR;
	u32 Reserved_4[2];
	u32 APB1LPENR;
	u32 APB2LPENR;
	u32 Reserved_5[2];
	u32 BDCR;
	u32 CSR;
	u32 Reserved_6[2];
	u32 SSCGR;
	u32 PLLI2SCFGR;
	u32 Reserved_7;
	u32 DCKCFGR;
}RCC_REG;

/*************************** 4- Variables **********************************/
static volatile RCC_REG *const RCC = (RCC_REG *const)(RCC_BaseAddress);

/*************************** 5- Implementation  ****************************/
/*
 * @brief : Function to Enable any clock source
 * @parameter : Clock Type
 * @return : Error States
 */
ErrorState RCC_EnableClock(u32 clk){

	    ErrorState loc_enumReturnError= RCC_enumOK;

		/*Enable a specific clock */
		RCC->CR |=clk;

		/*Wait until setting the ready flag or Time out */
		u16 timeOut =500;

		switch(clk)
		{
		case CLK_HSI:
			while((!(RCC->CR &HSI_READYFLAG))&&timeOut){
				timeOut--;
			}
			if(!(RCC->CR &HSI_READYFLAG)){
				loc_enumReturnError =RCC_enumClockNotReady;
			}else{
				/*do nothing*/
			}
			break;
		case CLK_HSE:
			while((!(RCC->CR &HSE_READYFLAG))&&timeOut){
				timeOut--;
			}
			if(!(RCC->CR &HSE_READYFLAG)){
				loc_enumReturnError =RCC_enumClockNotReady;
			}
			else{
			/*do nothing*/
			}
			break;

		case CLK_PLL:
			while((!(RCC->CR &PLL_READYFLAG))&&timeOut){
				timeOut--;
			}
			if(!(RCC->CR &PLL_READYFLAG)){
				loc_enumReturnError =RCC_enumClockNotReady;
			}else{
				/*do nothing*/
			}
			break;
		default:
			/*do nothing*/
		break;
		}
		return loc_enumReturnError;
}
/*
 * @brief : Function to Disable any clock source
 * @parameter : Clock Type
 * @return : void
 */
void RCC_DisableClock(u32 clk){
	RCC->CR &=(~clk);
}
/*
 * @brief : Function to Choose the system clock
 * @parameter : Clock Source
 * @return : void
 * */
void RCC_SelectClockSource(u32 sysClk){

	u32 temp = RCC->CFGR;
	/*Clear Register*/
	temp &= (~SYSCLK_MASK);
	/*Set new clock source*/
	temp |=sysClk;
	RCC->CFGR = temp;
}
/*
 * @brief :Function to Configure PLL Parameters
 * @Parameter : PLL Parameters
 * parameter[0] = 2 ≤ PLLM ≤ 63
 * parameter[1] = PLLP = 2,4,6,8
 * parameter[2] = 192 ≤ PLLN ≤ 432
 * parameter[3] =  2 ≤PLLQ ≤15
 *
 * @return: ErrorState
 * PLL Equation = f(PLL clock input) × (PLLN /(PLLM * PLLP))
 */

ErrorState RCC_ConfigurePLL(u32 PLLM,u32 PLLP,u32 PLLN,u32 PLLQ){

	  ErrorState loc_enumReturnError= RCC_enumNOK;

	  u32 loc_u32temp = RCC->PLLCFGR;

	  if(((PLLM < 2)||(PLLM > 63))||
	     ((PLLN < 192)||(PLLN > 432))||
		 ((PLLQ < 2)||(PLLQ > 15))||
		 (PLLP!=2)||(PLLP!=4)||(PLLP!=6)||(PLLP!=8)){

		  loc_enumReturnError= RCC_enumWrongPLLParameter;
	  }else{
		  loc_enumReturnError =RCC_enumOK;

		  /*Assign Parameters*/
		  loc_u32temp &= 0x00400000;


		  loc_u32temp |=((PLLM<<PLL_M_BITS)|(PLLN<<PLL_N_BITS)|(PLLQ<<PLL_Q_BITS)|(PLLP<<PLL_P_BITS));

		  RCC->PLLCFGR = loc_u32temp;
	  }
      return loc_enumReturnError;
}
/*
 * @brief:Function to Select PLL Source
 * @parameter: PLL Source (HSI or HSE)
 * @return: ErrorState
 * */
ErrorState RCC_SelectPLLSource(u8 source){

	ErrorState loc_enumReturnError= RCC_enumNOK;

	if((source==PLL_HSI)&&(HSI_READYFLAG == NOTREADY)){
		loc_enumReturnError = RCC_enumClockNotReady;

	}else if((source==PLL_HSE)&&(HSE_READYFLAG == NOTREADY)){
		loc_enumReturnError = RCC_enumClockNotReady;

	}else{
		loc_enumReturnError = RCC_enumOK;
		RCC->PLLCFGR |= (source<<PLL_SOURCE);
	}
	return loc_enumReturnError;
}
/*
 * @brief : Function to Configure Pre_scaler of AHB Bus
 * @Parameter :PreScaler
 * @return : void
 * */
void RCC_SelectAHBPrescaler(u32 prescaler){
	u32 loc_u32temp = RCC->CFGR;
	loc_u32temp &=AHB_CLEAR_MASK;
	loc_u32temp |=(prescaler<<AHB_BITS);
	RCC->CFGR = loc_u32temp;
}
/*
 * @brief : Function to Configure Pre_scaler of APB1 Bus
 * @Parameter :PreScaler
 * @return : void
 * */
void RCC_SelectAPB1Prescaler(u32 prescaler){
	u32 loc_u32temp = RCC->CFGR;
	loc_u32temp &= APB1_CLEAR_MASK;
	loc_u32temp |=(prescaler<<APB1_BITS);
	RCC->CFGR = loc_u32temp;
}
/*
 * @brief : Function to Configure Pre_scaler of APB2 Bus
 * @Parameter :PreScaler
 * @return : void
 * */
void RCC_SelectAPB2Prescaler(u32 prescaler){
	u32 loc_u32temp = RCC->CFGR;
	loc_u32temp &= APB2_CLEAR_MASK;
	loc_u32temp |= (prescaler<<APB2_BITS);
	RCC->CFGR = loc_u32temp;
}
/*
 * @brief : Function to Enable AHB Peripheral
 * @Parameter : Peripheral type
 * @return : void
 * */
void RCC_EnableAHBPeripherals(AHB_Peripheral_t peripheral){
	RCC->AHB1ENR |=(ENABLE<<peripheral);

}
/*
 * @brief : Function to Enable APB1 Peripheral
 * @Parameter : Peripheral type
 * @return : void
 * */
void RCC_EnableAPB1Peripherals(APB1_Peripheral_t peripheral){
	RCC->APB1ENR |=(ENABLE<<peripheral);
}

/*
 * @brief : Function to Enable APB2 Peripheral
 * @Parameter : Peripheral type
 * @return : void
 * */
void RCC_EnableAPB2Peripherals(APB2_Peripheral_t peripheral){
	RCC->APB2ENR |=(ENABLE<<peripheral);
}
/*
 * @brief : Function to Disable AHB Peripheral
 * @Parameter : Peripheral type
 * @return : void
 * */
void RCC_DisableAHBPeripherals(AHB_Peripheral_t peripheral){
	RCC->AHB1ENR &=~(ENABLE<<peripheral);
}
/*
 * @brief : Function to Disable APB1 Peripheral
 * @Parameter : Peripheral type
 * @return : void
 * */
void RCC_DisableAPB1Peripherals(APB1_Peripheral_t peripheral){
	RCC->APB1ENR &=~(ENABLE<<peripheral);
}

/*
 * @brief : Function to Disable APB2 Peripheral
 * @Parameter : Peripheral type
 * @return : void
 * */
void RCC_DisableAPB2Peripherals(APB2_Peripheral_t peripheral){
	RCC->APB2ENR &=~(ENABLE<<peripheral);
}
