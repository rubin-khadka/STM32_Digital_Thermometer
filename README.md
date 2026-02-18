# STM32F103C8 Digital Thermometer with 74HC595 and 7-Segment Display

![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)
![STM32](https://img.shields.io/badge/STM32-F103C8T6-blue)
![CubeMX](https://img.shields.io/badge/STM32-CubeMX-blueviolet)
![Keil](https://img.shields.io/badge/IDE-Keil--uVision5-darkgreen)

## Project Overview
This project implements a digital thermometer based on the **STM32F103C8T6 (Blue Pill)** microcontroller. Temperature data is acquired from an **LM35 analog temperature sensor** and displayed on a **4-digit 7-segment display**.

The display is controlled using **two daisy-chained 74HC595 shift registers over SPI**, minimizing GPIO usage. The ADC operates in **single-conversion, software-triggered mode**, with conversion results handled via **end-of-conversion interrupts**. All peripherals are configured **directly at the register level**, with **STM32CubeMX used only for initial clock and pin configuration**.

This project focuses on low-level embedded firmware design, real-time data acquisition, and efficient hardware interfacing.

### Project Variants
- **HAL-Based Version**: This repository - CubeMX for initial setup + register-level peripheral configuration
- **Bare-Metal Version**: [STM32_Digital_Thermometer_BareMetal](https://github.com/rubin-khadka/STM32_Digital_Thermometer_BareMetal) - Complete register-level implementation (no CubeMX/HAL)

For a more advanced version of this project with multiple temperature sensors, Direct Memory Access (DMA), and data logging capabilities check out: 
🔗 [STM32_Thermometer_DataLogger](https://github.com/rubin-khadka/STM32_Thermometer_DataLogger)

### Hardware Components
- **MCU**: STM32F103C8T6 (Blue Pill)  
    - [STM32 Blue Pill Essential Circuits](https://github.com/rubin-khadka/STM32_Digital_Thermometer/blob/main/Docs/STM32_Bluepill_Circuit.png)
- **Temperature Sensor**: LM35 (10 mV/°C)
- **Display**: 4-digit common-cathode 7-segment display
- **Display Driver**: 2 × 74HC595 shift registers (daisy-chained)
- **Interface**: SPI1 (data) + GPIO (latch control)

### System Configuration
The system is configured for deterministic timing and stable ADC sampling.

- System Clock: 64 MHz (HSI PLL)
    - [STM32 Clock Configuration](https://github.com/rubin-khadka/STM32_Digital_Thermometer/blob/main/Media/Clock_configuration.png)
- SPI1:
    - Data Size: 16-bit mode
    - Baud Rate: 16 MBits/s (derived from APB2 prescaler)
    - Mode: Master, Full-Duplex
    - Clock Polarity: Low, Phase: 1 Edge
    - First Bit: MSB
- ADC1:
    - ADC Clock: 10.667 MHz
    - Resolution: 12-bit
    - Sampling Time: 28.5 cycles
    - Channel: PA0 (ADC1_IN0)

### Development & Testing
- Firmware developed in `Keil MDK-ARM 5`
- Circuit simulation and validation in `Proteus 8`

## Video Demonstrations

### Proteus Demonstration

https://github.com/user-attachments/assets/aaacc959-ffa7-4ffb-9543-2609d38a994c

Demonstration of the digital thermometer:
- Starts at 1.0 °C, demonstrating basic temperature display functionality
- Both positive and negative temperature readings
- Voltage divider circuit for negative temperature measurement
- Measurement accuracy within ±0.1°C tolerance 

## Project Schematic Diagram
<img width="1223" height="656" alt="STM32_Digital_Thermometer_Schematic_complete" src="https://github.com/user-attachments/assets/4e52997d-1e72-4469-97db-91ec9aa370eb" />
*Schematic designed using EasyEDA*

The schematic shows the complete STM32F103C8T6 implementation including:
- Core Blue Pill circuits: Power supply, 8MHz and RTC clock, reset circuit, decoupling and BOOT circuit
- Display driver: Two daisy-chained 74HC595 shift registers controlling the 4-digit 7-segment display
- Temperature sensing: LM35 sensor with voltage divider for negative temperature measurement

## Pinout Documentation

#### STM32F103C8T6 Pin Configuration

| STM32 Pin | Function | Connected To | Purpose |
|-----------|----------|--------------|---------|
| `PA5` | `SPI1_SCK` | Both 74HC595 SH_CP (Pin 11) | Shift Clock - data synchronization |
| `PA7` | `SPI1_MOSI` | First 74HC595 DS (Pin 14) | Serial Data - segment/digit data |
| `PA4` | `GPIO Output` | Both 74HC595 ST_CP (Pin 12) | Latch Control - update outputs |
| `PA0` | `ADC1_IN0` | LM35 Output | Temperature sensor reading |

#### First 74HC595 (Segment Control)
| 74HC595 Pin | Connection | Purpose |
|-------------|------------|---------|
| `Q0` | Segment A | Display segment A |
| `Q1` | Segment B | Display segment B |
| `Q2` | Segment C | Display segment C |
| `Q3` | Segment D | Display segment D |
| `Q4` | Segment E | Display segment E |
| `Q5` | Segment F | Display segment F |
| `Q6` | Segment G | Display segment G |
| `Q7` | Decimal Point | Display decimal point |
| `Q7'/QH'` | Second 74HC595 DS (Pin 14) | Daisy-chain connection |

#### Second 74HC595 (Digit Control)
| 74HC595 Pin | Connection | Purpose |
|-------------|------------|---------|
| `Q0` | Digit 1 Cathode | Activate Digit 1 |
| `Q1` | Digit 2 Cathode | Activate Digit 2 |
| `Q2` | Digit 3 Cathode | Activate Digit 3 |
| `Q3` | Digit 4 Cathode | Activate Digit 4 |
| `Q4-Q7` | Not Connected | Unused outputs |

#### Voltage Divider Circuit (Negative Temperature Measurement)
| Component | Connection Points | Purpose |
|-----------|-------------------|---------|
| `R1 (10kΩ)` | 3.3V → R1 → R2 | Creates voltage divider for 1.65V reference |
| `R2 (10kΩ)` | R1 → R2 → GND | Sets midpoint voltage at 1.65V |
| `LM35 GND` | R1-R2 junction → LM35 GND | Shifts LM35 ground to 1.65V for negative readings |

#### STM32 Pin Configuration
<img width="652" height="647" alt="Pin_config_stm32" src="https://github.com/user-attachments/assets/afe6aaad-1ce1-4ff5-a11b-04cd4aa4fab2" />

## Quick Start

### Prerequisites
- STM32F103C8T6 (Blue Pill) Microcontroller
- STM32CubeF1 Firmware Package (includes HAL drivers)
- Keil MDK-ARM 5 with STM32 support
- STM32CubeMX for initial project setup
- Proteus 8 to run the simulation file
- ST-Link Programmer/Debugger

### Setup

1. Clone this repository
```bash
git clone https://github.com/rubin-khadka/STM32_Digital_Thermometer.git
```
2. Open **CubeMX** file `STM32_Digital_Thermometer.ioc` in STM32CubeMX

3. `Generate code` in CubeMX - this will open the project in Keil 5

4. Build the project and test it with:
    - Actual hardware, OR
    - Proteus 8 simulation `Proteus_Simulation.pdsprj`

#### Alternative Setup (Without Keil)
If you don't have Keil MDK:
1. In **CubeMX** file `STM32_Digital_Thermometer.ioc`, configure the project for STM32Cube IDE
2. Copy files from `Core/Src` and `Core/Inc` folders
3. Copy code from `main.c` file
4. Build in STM32Cube IDE and test

The project should work with either development environment.

## Resources
- [STM32F103 Datasheet](https://www.st.com/resource/en/datasheet/stm32f103c8.pdf)
- [74HC595 Shift Register Datasheet](https://www.ti.com/lit/ds/symlink/sn74hc595.pdf?spm=a2ty_o01.29997173.0.0.16bf5171zm4QVo&file=sn74hc595.pdf)
- [LM35 Temperature Sensor Datasheet](https://www.ti.com/lit/ds/symlink/lm35.pdf?spm=a2ty_o01.29997173.0.0.16bf5171zm4QVo&file=lm35.pdf)
- [EasyEDA Website](https://easyeda.com/)

## What This Project Demonstrates
- Register-level STM32 peripheral programming without reliance on HAL drivers
- Interrupt-driven ADC data acquisition for real-time temperature measurement
- Efficient GPIO utilization using SPI-based shift registers
- Hardware–software co-design, including analog signal conditioning for negative temperatures
- Clear, structured embedded documentation aligned with production-level practices

## Project Status
- **Status**: Complete
- **Version**: v1.0
- **Last Updated**: December 2025

## Contact
**Rubin Khadka Chhetri**  
📧 rubin.robotic@gmail.com  
🐙 GitHub: https://github.com/rubin-khadka
