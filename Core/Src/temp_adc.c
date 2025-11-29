/**
  * @file    temp_adc.c
  * @brief   Temperature ADC module - Register level implementation
  * @author  Rubin Khadka
  */
	
#include "temp_adc.h"

/* Global Variables */
volatile uint32_t adc_raw_value = 0;
volatile uint8_t adc_conversion_complete = 0;

/* Initialize ADC1 Channel 0 for temperature measurement */
void temp_adc_init(void)
{
	// Enable ADC1 clock
	RCC->APB2ENR |= RCC_APB2ENR_ADC1EN;
	
	// Power on ADC
	ADC1->CR2 |= ADC_CR2_ADON;
	
	// Configure Sampling time for Channel 0
	ADC1->SMPR2 &= ~(0x07 << 0);		// Clear existing sampling cycle
	ADC1->SMPR2 |= (TEMP_ADC_SAMPLING_TIME << 0);		// Set sampling cycle 28.5 
	
	// Configure conversion sequence 
	ADC1->SQR1 &= ~(0x0F << 20);   	// 1 conversion in sequence
	ADC1->SQR3 = TEMP_ADC_CHANNEL;  // SQ1[4:0] = Channel 0
	
	// ADC calibration 
	ADC1->CR2 |= ADC_CR2_RSTCAL;
	while (ADC1->CR2 & ADC_CR2_RSTCAL);
	
	ADC1->CR2 |= ADC_CR2_CAL;
	while (ADC1->CR2 & ADC_CR2_CAL);
	
	// Final configuration
	ADC1->CR2 &= ~ADC_CR2_CONT;  // Single conversion mode
	ADC1->CR2 &= ~ADC_CR2_ALIGN; // Right alignment
	
	// Enable ADC interrupt in NVIC
	ADC1->CR1 |= ADC_CR1_EOCIE;
	NVIC_EnableIRQ(ADC1_2_IRQn);   
		
	// Clear any previous values 
	adc_raw_value = 0;
	adc_conversion_complete = 0;
	
	// Brief stabilization delay
	for (volatile uint32_t i = 0; i < 100000; i++);  // Approx 1ms delay
}

void temp_adc_start_conversion(void)
{
	adc_conversion_complete = 0;
	ADC1->CR2 |= (0x01 << 22);
//	ADC1->CR2 |= ADC_CR2_SWSTART;
}

uint8_t temp_adc_is_ready(void)
{
	return adc_conversion_complete;
}

float temp_adc_read_celsius(void)
{
    float voltage = (adc_raw_value * VREF) / ADC_RESOLUTION;
		float temperature = (voltage - 1.65f) * LM35_SCALE_FACTOR;
    return temperature;
}

void ADC1_2_IRQHandler(void)
{
	if (ADC1->SR & ADC_SR_EOC)
	{
		adc_raw_value = ADC1->DR;
		adc_conversion_complete = 1;
		ADC1->SR &= ~ADC_SR_EOC;
	}
}


