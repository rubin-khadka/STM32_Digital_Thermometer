	
#ifndef SPI_H
#define SPI_H

#ifdef __cplusplus
extern "C" {
#endif

/* Include Definitions */
#include "main.h"

/* Macros */
#define Latch(x) (x==1 ? (HAL_GPIO_WritePin(SPI_SS, SPI_SS_Pin, GPIO_PIN_SET)) : \
												 (HAL_GPIO_WritePin(SPI_SS, SPI_SS_Pin, GPIO_PIN_RESET)))

// Usage
/* 
	LATCH(1);	Set latch high
	LATCH(0); Set latch low  
	*/

// Pulse latch macro
#define LATCH_PULSE() do { \
    LATCH(1); \
    for(volatile int i = 0; i < 10; i++); \
    LATCH(0); \
} while(0)

#ifdef __cplusplus
}
#endif

#endif /* SPI_H */