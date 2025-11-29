
#include "spi.h"

const uint8_t digit_patterns[10] = {
    0x3F, // 0: A,B,C,D,E,F
    0x06, // 1: B,C
    0x5B, // 2: A,B,D,E,G
    0x4F, // 3: A,B,C,D,G
    0x66, // 4: B,C,F,G
    0x6D, // 5: A,C,D,F,G
    0x7D, // 6: A,C,D,E,F,G
    0x07, // 7: A,B,C
    0x7F, // 8: A,B,C,D,E,F,G
    0x6F  // 9: A,B,C,D,F,G
};

void SPI1_Transmit16(uint16_t data) {
    // Wait until TX buffer is empty
    while (!(SPI1->SR & SPI_SR_TXE)) {
        // Wait for TXE flag
    }
    
    // Write 16-bit data to Data Register
    SPI1->DR = data;
    
    // Wait for transmission to complete
    while (SPI1->SR & SPI_SR_BSY) {
        // Wait while SPI is busy
    }
    
    // Clear RX buffer by reading DR
    volatile uint16_t dummy = SPI1->DR;
    (void)dummy;
}

