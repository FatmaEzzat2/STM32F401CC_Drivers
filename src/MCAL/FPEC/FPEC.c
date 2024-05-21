/********************************************************************************************************/
/************************************************Includes************************************************/
/********************************************************************************************************/
#include"FPEC.h"



/********************************************************************************************************/
/************************************************Defines*************************************************/
/********************************************************************************************************/

#define BASE_ADDRESS    0x40023C00

#define BUSY_BIT            16
#define SER_BIT             1       /*Sector Erase*/
#define SNB_BIT             3       /*Sector Number*/   
#define LOCK_BIT            31    
#define STRT_BIT            16  
#define EOP_BIT             0
#define SECT_MASK           0b1111
#define PG_BIT              0
#define PSIZE               8
#define PSIZE_MASK          0b11
#define KEY_1           0x45670123
#define KEY_2           0xCDEF89AB

/********************************************************************************************************/
/************************************************Types***************************************************/
/********************************************************************************************************/
typedef struct 
{
    u32 ACR;    
    u32 KEYR;
    u32 OPTKEYR;
    u32 SR;
    u32 CR;
    u32 OPTCR;
}FPEC;


/********************************************************************************************************/
/************************************************Variables***********************************************/
/********************************************************************************************************/

static volatile FPEC *const FPEC_REG = (volatile FPEC *const)BASE_ADDRESS;

/********************************************************************************************************/
/*****************************************Static Functions Prototype*************************************/
/********************************************************************************************************/



/********************************************************************************************************/
/*********************************************APIs Implementation****************************************/
/********************************************************************************************************/

/*To erase a sector*/
void FPEC_voidFlashSectorErase(u8 Copy_u8SectorNumber){

    /* Check that no Flash memory operation is ongoing by checking the BSY bit */
    while ((FPEC_REG->SR>>BUSY_BIT)&1);

    /*First, We need to unlocking the Flash control register. In case It is locked*/
    if(((FPEC_REG->CR>>LOCK_BIT)&1)==ENABLE){

        FPEC_REG->KEYR = KEY_1;
        FPEC_REG->KEYR = KEY_2;

        /*Ensure that the Flash control register is unlocked now*/
        while((FPEC_REG->CR>>LOCK_BIT)&1);
    }
   

    /*Select the sector out of the 5 sectors*/
    FPEC_REG->CR &=~(SECT_MASK<<SNB_BIT);
    FPEC_REG->CR |=(Copy_u8SectorNumber<<SNB_BIT);

    /*Enable Sector Erase*/
    FPEC_REG->CR |=(ENABLE<<SER_BIT);   

    /*Start Erasing*/
    FPEC_REG->CR |=(ENABLE<<STRT_BIT);

   /*Wait to flash ends the operation*/
    while ((FPEC_REG->SR>>BUSY_BIT)&1);

   /*Clear End of operation flag*/
    FPEC_REG->SR |=(ENABLE<<EOP_BIT);

    /*Diactivate Sector erase enable*/
    FPEC_REG->CR &=~(ENABLE<<SER_BIT); 
}
void FPEC_voidFlashWrite(u32 Copy_u32MemoryAddress, u64* Copy_u16Data, u8 Copy_u8PageSize){

    /* Check that no Flash memory operation is ongoing by checking the BSY bit */
    while ((FPEC_REG->SR>>BUSY_BIT)&1);

    /*First, We need to unlocking the Flash control register. In case It is locked*/
    if(((FPEC_REG->CR>>LOCK_BIT)&1)==ENABLE){

        FPEC_REG->KEYR = KEY_1;
        FPEC_REG->KEYR = KEY_2;

        /*Ensure that the Flash control register is unlocked now*/
        while((FPEC_REG->CR>>LOCK_BIT)&1);
    }

    /* Set the PG bit */
    FPEC_REG->CR |=(ENABLE<<PG_BIT); 

    /*Action*/
    /*Select Half Word*/
    FPEC_REG->CR &=~(ENABLE<<PSIZE);
    FPEC_REG->CR |=(Copy_u8PageSize<<PSIZE);






    /*Wait for the BSY bit to be cleared*/
    while ((FPEC_REG->SR>>BUSY_BIT)&1);

   /*Clear End of operation flag*/
    FPEC_REG->SR |=(ENABLE<<EOP_BIT);

    /*Diactivate Page program enable*/
    FPEC_REG->CR &=~(ENABLE<<PG_BIT); 

}
