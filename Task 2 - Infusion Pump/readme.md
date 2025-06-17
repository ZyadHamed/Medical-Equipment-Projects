# Medical Infusion Pump Controller

A volumetric infusion pump system implemented with Arduino, featuring real-time flow rate monitoring and safety alarms for medical liquid drug delivery.

## Overview

This project implements a medical infusion pump controller that accurately dispenses liquid medication at controlled rates. The system includes real-time flow monitoring, volume tracking, and safety features including occlusion detection.

## Screenshots and videos showcasing the task:
A front view of the project's prototype:
![Prototype](https://github.com/user-attachments/assets/2b8e7f68-53ae-418f-a84e-e737b628b433)

A front view of the prototype working after adding 300 mL to be infused from the laptop's serial input:

https://github.com/user-attachments/assets/7169d037-6a72-4854-ba79-a83a6273fbc7

The corrosponding top view:

https://github.com/user-attachments/assets/1ae45b2c-d21e-4989-8812-0e1f54852adf


## Features

- Volumetric flow rate control
- Real-time flow rate monitoring
- Accumulated volume tracking
- LCD display showing current flow rate and volume
- Occlusion detection and alarm system
- Serial interface for volume input
- Safety cutoff mechanisms

## Hardware Components

- Arduino microcontroller
- Flow rate sensor (450 pulses/liter calibration)
- I2C LCD display (16x2 characters)
- Buzzer for alarm
- Peristaltic pump
- Power supply system

## Safety Features

- Occlusion detection (flow rate < 2 mL/s)
- Over-flow protection (flow rate > 115 mL/s)
- Automatic pump shutdown on error detection
- Audible alarm system
- Empty reservoir detection
- Air-in-line detection

## Technical Specifications

- Flow rate measurement range: 2-115 mL/s
- Flow rate update interval: 100ms
- Flow sensor resolution: 450 pulses/liter
- Display update rate: Real-time
- Serial communication: 9600 baud

## Operation

1. System initialization
2. Volume input via serial interface
3. Continuous monitoring of:
   - Flow rate
   - Accumulated volume
   - System errors
4. Automatic shutdown upon:
   - Target volume reached
   - Error detection
   - Occlusion detection

## Display Information

- Current flow rate (mL/s)
- Accumulated volume (mL)
- Error messages
- Completion status

## Error Handling

- Occlusion detection and alarm
- Flow rate out of range detection
- Empty reservoir detection
- Automatic pump shutdown
- Visual and audible alerts

## Installation

1. Connect hardware components according to pin configuration
2. Upload code to Arduino
3. Configure serial monitor to 9600 baud
4. Input desired volume when prompted

## Pin Configuration

- Flow Sensor: Pin 2
- Pump Control: Pin 3
- Buzzer: Pin 4
- LCD: I2C (SDA/SCL)
- Direction Control: Pins 7,8

## Safety Notes

This system is designed for educational/demonstration purposes. For medical use, additional safety features and certifications would be required.
