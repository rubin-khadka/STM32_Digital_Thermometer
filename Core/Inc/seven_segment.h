
#ifndef SEVEN_SEGMENT_H
#define SEVEN_SEGMENT_H

#ifdef __cplusplus
extern "C" {
#endif

/* Include Definitions */
#include "spi.h"

// Digit Control Masks (Bits 15-8 of 16-bit SPI data)
#define DIGIT_1  0xFE00  // 1111 1110 0000 0000 
#define DIGIT_2  0xFD00  // 1111 1101 0000 0000
#define DIGIT_3  0xFB00  // 1111 1011 0000 0000
#define DIGIT_4  0xF700  // 1111 0111 0000 0000

// Special digit values for the segment pattern array
#define DIGIT_BLANK     10    // Value for blank digit
#define DIGIT_DP        11    // Value for decimal point only
#define DIGIT_MINUS     12    // Value for minus sign

/* Structure to hold the temperature data */
typedef struct
{
	uint8_t digit1;  // Handles negative 
	uint8_t digit2;  // digit (0-9)
	uint8_t digit3;  // Decimal point + digit
	uint8_t digit4;  // digit (0-9)
}DisplayDigits_t;

/* Function Prototypes */
void Temperature_To_Digit(float temperature, DisplayDigits_t *digits);
void Update_Display(const DisplayDigits_t *digits);

#ifdef __cplusplus
}
#endif

#endif /* SEVEN_SEGMENT_H */