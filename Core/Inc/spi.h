
#ifndef SPI_H
#define SPI_H

#ifdef __cplusplus
extern "C" {
#endif

/* Include Definitions */
#include "main.h"

/* Macros */
#define LATCH(x) (x==1 ? (HAL_GPIO_WritePin(SPI_SS_GPIO_Port, SPI_SS_Pin, GPIO_PIN_SET)):\
												 (HAL_GPIO_WritePin(SPI_SS_GPIO_Port, SPI_SS_Pin, GPIO_PIN_RESET)))

/* Function Prototypes */
void SPI1_init(void);
void SPI1_Transmit16(uint16_t data);

#ifdef __cplusplus
}
#endif

#endif /* SPI_H */