
#include "seven_segment.h"

const uint8_t digit_patterns[13] = 
{
	0x3F, // 0: A,B,C,D,E,F
	0x06, // 1: B,C
	0x5B, // 2: A,B,D,E,G
	0x4F, // 3: A,B,C,D,G
	0x66, // 4: B,C,F,G
	0x6D, // 5: A,C,D,F,G
	0x7D, // 6: A,C,D,E,F,G
	0x07, // 7: A,B,C
	0x7F, // 8: A,B,C,D,E,F,G
	0x6F,	// 9: A,B,C,D,F,G
	0x00, // 10: Blank - No segments
	0x80, // 11: Decimal Point - DP only
	0x40  // 12: Minus sign - Segment G only
};

const uint8_t digit_patterns_with_dp[10] = {
	0xBF, // 0 with decimal point
	0x86, // 1 with decimal point  
	0xDB, // 2 with decimal point
	0xCF, // 3 with decimal point
	0xE6, // 4 with decimal point
	0xED, // 5 with decimal point
	0xFD, // 6 with decimal point
	0x87, // 7 with decimal point
	0xFF, // 8 with decimal point
	0xEF  // 9 with decimal point
};

void Temperature_To_Digit(float temperature, DisplayDigits_t *digits)
{
	if (temperature < 0.0f)
	{
		digits->digit1 = DIGIT_MINUS;
		temperature = -temperature;
	}
	else
	{
		digits->digit1 = DIGIT_BLANK;
	}
	
	// Multiply by 10 to eliminate the decimal point
	int temp_x10 = (int)(temperature * 10.0f);
	
	// Extract digits from integers
	int tens_digit = temp_x10 / 100;           
	int ones_digit = (temp_x10 / 10) % 10;    
	int tenths_digit = temp_x10 % 10;
	
	if (digits->digit1 == DIGIT_BLANK)
	{
		if (tens_digit == 0)
		{
			digits->digit2 = DIGIT_BLANK;
		} else
		{
			digits->digit2 = tens_digit;
		}
	}
	
	digits->digit3 = ones_digit;
	digits->digit4 = tenths_digit;
}

void Update_Display(const DisplayDigits_t *digits)
{
	// Display Digit 1 (Tens place or minus sign)
	uint16_t data1 = DIGIT_1 | digit_patterns[digits->digit1];
	LATCH(0);
	SPI1_Transmit16(data1);
	LATCH(1);
	HAL_Delay(3);
	
	// Display Digit 2 (Ones place WITH decimal point)
	uint16_t data2 = DIGIT_2 | digit_patterns[digits->digit2];
	LATCH(0);
	SPI1_Transmit16(data2);
	LATCH(1);
	HAL_Delay(3);
	
	// Display Digit 3 (Tenths place)
	uint16_t data3 = DIGIT_3 | digit_patterns_with_dp[digits->digit3];
	LATCH(0);
	SPI1_Transmit16(data3);
	LATCH(1);
	HAL_Delay(3);
	
	// Display Digit 4 (Blank - unused)
	uint16_t data4 = DIGIT_4 | digit_patterns[digits->digit4];
	LATCH(0);
	SPI1_Transmit16(data4);
	LATCH(1);
	HAL_Delay(3);
}

