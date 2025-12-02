# STM32F103C8 Temperature Display with 74HC595 & 7-Segment Display

## Project Overview
A digital thermometer using STM32F103C8T6 (Blue Pill) that reads temperature from an LM35 sensor and displays it on a 4-digit 7-segment display using two daisy-chained 74HC595 shift registers. The project features register-level ADC reading and SPI communication for optimal performance, providing real-time temperature measurement. 

***Note***: EEPROM and memory card module implementation planned for future version.

### Hardware Components
- MCU: STM32F103C8T6 (Blue Pill)
- Temperature Sensor: LM35 (10mV/°C)
- Display: 4-digit Common Cathode 7-Segment Display
- Shift Registers: 2x 74HC595 (daisy-chained)
- Communication: SPI1 for data transfer and GPIO for latch control

### System Configuration
- System Clock: 64 MHz (HSI PLL)
- SPI1:
    - Data Size: 16-bit mode
    - Baud Rate: 16 MBits/s
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

https://github.com/user-attachments/assets/aaacc959-ffa7-4ffb-9543-2609d38a994c

Demonstration of the digital thermometer:
- Starts at 1.0°C showing basic temperature display functionality
- Both positive and negative temperature readings
- Voltage divider circuit for negative temperature measurement
- Measurement accuracy within ±0.1°C tolerance 

## Project Schematic Diagram
<img width="1118" height="593" alt="STM32 Digital_Thermometer_Schematic_complete" src="https://github.com/user-attachments/assets/b7086b7e-cc3f-4433-afcc-69bc082da428" />

*Schematic designed using EasyEDA*

The schematic shows the complete STM32F103C8T6 implementation including:
- Core Blue Pill circuits: Power supply, 8MHz and RTC clock, reset circuit, decoupling and BOOT circuit
- Display driver: Two daisy-chained 74HC595 shift registers controlling the 4-digit seven segment display
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
- [74HC595 Datasheet](https://www.ti.com/lit/ds/symlink/sn74hc595.pdf?spm=a2ty_o01.29997173.0.0.16bf5171zm4QVo&file=sn74hc595.pdf)
- [LM35 Datasheet](https://www.ti.com/lit/ds/symlink/lm35.pdf?spm=a2ty_o01.29997173.0.0.16bf5171zm4QVo&file=lm35.pdf)
- [EasyEDA Website](https://easyeda.com/)

## Project Status
**Status**: Complete  
**Version**: v1.0  
**Last Updated**: December 2025

## Contact
**Rubin Khadka Chhetri**
- Email: rubin.robotic@gmail.com
- GitHub: [@rubin-khadka](https://github.com/rubin-khadka)
