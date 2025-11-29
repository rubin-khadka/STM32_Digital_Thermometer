#include "spi.h"

void SPI1_init(void)
{
	SPI1->CR1 |= SPI_CR1_SPE; // Enable SPI
}

void SPI1_Transmit16(uint16_t data) 
{
	// Wait until TX buffer is empty
	while (!(SPI1->SR & SPI_SR_TXE)) {
	}

	// Write 16-bit data to Data Register
	SPI1->DR = data;

	// Wait for transmission to complete
	while (SPI1->SR & SPI_SR_BSY) {
	}

	// Clear RX buffer by reading DR
	volatile uint16_t dummy = SPI1->DR;
	(void)dummy;
}