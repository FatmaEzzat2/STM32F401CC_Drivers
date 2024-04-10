/*
*File:  Header File  of UART Registers
*Author:  Fatma Ezzat
*Created: 4/7/2024
*Target:  STM32F401cc
*/

#ifndef MCAL_UART_UART_VALIDATION_H_
#define MCAL_UART_UART_VALIDATION_H_
/************************************************************************/
/*					          Status Register                           */
/************************************************************************/
#define CTS     9
#define LBD     8
#define TXE     7
#define TC      6
#define RXNE    5
#define IDLE    4  
#define ORE     3
#define NF      2
#define FE      1
#define PE      0
/************************************************************************/
/*					          Control Register 1                        */
/************************************************************************/
#define OVER8   15
#define UE      13
#define M       12
#define WAKE    11
#define PCE     10
#define PS      9
#define PEIE    8
#define TXEIE   7
#define TCIE    6
#define RXNEIE  5
#define IDLEIE  4
#define TE      3
#define RE      2
#define RWU     1
#define SBK     0
/************************************************************************/
/*					          Control Register 2                        */
/************************************************************************/

#define LINEN   14
#define STOP    12
#define CLKEN   11
#define CPOL    10
#define CPHA    9
#define LBCL    8
#define LBDIE   6
#define LBDL    5
#define ADD     0
/************************************************************************/
/*					          Control Register 3                        */
/************************************************************************/

#define ONEBIT  11
#define CTSIE   10
#define CTSE    9
#define RTSE    8
#define DMAT    7
#define DMAR    6
#define SCEN    5
#define NACK    4
#define HDSEL   3
#define IRLP    2
#define IREN    1
#define EIE     0
#endif // MCAL_UART_UART_VALIDATION_H_