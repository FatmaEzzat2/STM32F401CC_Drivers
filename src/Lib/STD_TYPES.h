
#ifndef STD_TYPES_H_
#define STD_TYPES_H_

typedef unsigned char u8;
typedef unsigned short int u16;
typedef unsigned long int u32;
typedef unsigned long long int u64;


typedef signed char s8;
typedef signed short int s16;
typedef signed long int s32;

typedef float f32;
/*
 *@brief :  Logic State Type : HIGH (5V) or LOW(0V )
 */
typedef enum
{
	LogicLow,
	LogicHigh
}LogicState_t;

#define NULL (void*)0
#endif /* STD_TYPES_H_ */
