/**
  * @file    temp_adc.h
  * @brief   Temperature ADC module for STM32F103 using LM35 sensor
  * @author  Rubin Khadka
  */
	
#ifndef TEMP_ADC_H
#define TEMP_ADC_H

#ifdef __cplusplus
extern "C" {
#endif

/* Include Definitions */
#include "main.h"

/* Defines */
#define TEMP_ADC_CHANNEL 				0x00		// ADC Channel 0 (PA0)
#define TEMP_ADC_SAMPLING_TIME 	0x03		// 28.5 sampling cycle

// Temperature calculation
#define VREF    								3.3f 		// 3.3V reference in mV
#define ADC_RESOLUTION      		4095.0f // 12-bit ADC
#define LM35_SCALE_FACTOR     	100.0f 	// LM35: 10mV/°C = 0.01V/°C × 100

// Integer-based constants
#define VREF_MV 3300        // 3.3V in millivolts
#define ADC_RESOLUTION_INT 4095 // 12-bit ADC
#define VIRTUAL_GROUND_MV 1650  // 1.65V in millivolts

/* Global Variables */
extern volatile uint32_t adc_raw_value;
extern volatile uint8_t adc_conversion_complete;

/* Function Prototypes */
void temp_adc_init(void);
void temp_adc_start_conversion(void);
uint8_t temp_adc_is_ready(void);
float temp_adc_read_celsius(void);
void ADC1_2_IRQHandler(void);

#ifdef __cplusplus
}
#endif

#endif /* TEMP_ADC_H */