# STM32F103C8 Temperature Display with 74HC595 & 7-Segment Display

## Project Overview
A digital thermometer using STM32F103C8T6 (Blue Pill) that reads temperature from an LM35 sensor and displays it on a 4-digit 7-segment display using two daisy-chained 74HC595 shift registers. The project features register-level ADC reading and SPI communication for optimal performance, providing real-time temperature measurement.

### Hardware Components
- MCU: STM32F103C8T6 (Blue Pill)
- Temperature Sensor: LM35 (10mV/°C)
- Display: 4-digit Common Cathode 7-Segment Display
- Shift Registers: 2x 74HC595 (daisy-chained)
- Communication: SPI1 for data transfer and GPIO for latch control

### Development & Testing
- Firmware developed in Keil MDK-ARM 5
- Circuit simulation and validation in Proteus 8

### Future Enhancements
- EEPROM integration for storing temperature calibration data and settings
- Memory card module for data logging and long-term temperature tracking

## Project Schematic Diagram
<img width="1118" height="593" alt="STM32 Digital_Thermometer_Schematic_complete" src="https://github.com/user-attachments/assets/b7086b7e-cc3f-4433-afcc-69bc082da428" />

*Schematic designed using EasyEDA*

The schematic shows the complete STM32F103C8T6 implementation including:
- Core Blue Pill circuits: Power supply, 8MHz and RTC clock, reset circuit, decoupling and BOOT circuit
- Display driver: Two daisy-chained 74HC595 shift registers controlling the 4-digit seven segment display
- Temperature sensing: LM35 sensor with voltage divider for negative temperature measurement

## Video Demonstration


https://github.com/user-attachments/assets/aaacc959-ffa7-4ffb-9543-2609d38a994c


## Quick Start
### Prerequisites
### Setup
