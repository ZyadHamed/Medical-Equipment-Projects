# Hemodialysis Machine Safety System

A prototype hemodialysis machine with advanced safety features including motion detection, blood leak monitoring, and bubble detection systems.

## Overview

This project implements an intelligent safety monitoring system for hemodialysis machines, featuring multiple sensors and alarms to enhance patient safety during treatment. The system includes novel needle displacement detection using accelerometer data.

## Key Features

- Needle displacement detection via MPU6050
- Blood leak detection using color sensing
- Air bubble detection through IR sensing
- Real-time temperature monitoring
- Automated pump control system
- Multiple safety alarms
- LCD status display

## Hardware Components

- Arduino microcontroller
- MPU6050 (accelerometer/gyroscope)
- TCS230 color sensor
- Dallas temperature sensor
- IR sensor for bubble detection
- I2C LCD display
- Dual pump system:
  - Blood pump
  - Dialysate pump
- Multiple alarm indicators

## Safety Systems

### Motion Detection System
- Monitors sudden needle movement
- Accelerometer threshold: 0.5g
- Immediate pump shutdown on detection
- Audio-visual alerts

### Blood Leak Detection
- RGB color sensing
- Continuous monitoring
- Automatic pump shutdown
- Configurable sensitivity

### Bubble Detection
- IR sensor monitoring
- Detection range: 200-250 units
- Immediate alert system
- Automatic safety protocols

## Technical Specifications

- I2C Communication: 400kHz
- Gyro Calibration Samples: 2000
- Temperature Monitoring Rate: Real-time
- Color Sensor Sampling: 200ms intervals
- Multiple alarm outputs
- Dual pump control system

## Control Features

### Pump Control
- Automated blood pump management
- Dialysate flow control
- Safety-triggered shutoff
- Independent pump control

### Monitoring Display
- Real-time temperature
- System status
- Error conditions
- Alert messages

## Safety Protocols

1. Immediate pump shutdown on:
   - Needle displacement
   - Blood leak detection
   - Air bubble detection
2. Visual and audible alerts
3. System status display
4. Automatic flow control

## Installation

1. Connect sensors according to pin configuration
2. Upload Arduino code
3. Calibrate MPU6050
4. Set detection thresholds
5. Verify alarm systems
6. Test safety protocols

## Pin Configuration

- Blood Pump: Pin 4
- Dialysate Pump: Pin 5
- Color Sensor: Pins 6,7,9,10
- Bubble Sensor: Pin A0
- Temperature Sensor: Pin 13
- Alarm Outputs: Pins 2,11,12

## Safety Notes

This is a prototype system for demonstration purposes. Medical certification and additional safety features would be required for clinical use.
