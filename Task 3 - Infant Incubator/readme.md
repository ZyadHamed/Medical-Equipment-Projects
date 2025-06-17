# Infant Incubator System

A prototype infant incubator with automated temperature control, environmental monitoring, and safety features designed for neonatal care.

## Overview

This project implements an intelligent infant incubator system that maintains optimal environmental conditions through automated temperature control and monitoring. The system features dual heating and cooling mechanisms, along with real-time environmental parameter tracking.

## Screenshots and videos showcasing the task:

Visible external shape of the project's prototype:
![VisisbleShapeOfPrototype](https://github.com/user-attachments/assets/5b6ad20f-8be2-40f9-904c-e6429ff68702)

Internal electronics of the project's prototype:
![InternalStructureOfPrototype](https://github.com/user-attachments/assets/2f4ee370-ff66-4053-8279-c2d70da29d2d)

The prototype working with a demonstration of tempearture control:


https://github.com/user-attachments/assets/e3b8eae1-244f-4857-b288-3d099f570964




## Features

- Automated temperature control system
- Dual fan configuration for heating and cooling
- Real-time temperature and humidity monitoring
- LCD display for environmental parameters
- Baby temperature monitoring
- Protective transparent observation window
- Lightweight yet durable foam construction

## Hardware Components

- Arduino microcontroller
- DHT11 temperature and humidity sensor
- Dallas temperature sensor for baby monitoring
- I2C LCD display (16x2 characters)
- Incandescent heat lamp
- Brushless DC fan for heat distribution
- 220V AC fan for cooling
- H-bridge motor controller
- Foam insulation structure
- Transparent plastic observation panels

## Technical Specifications

- Temperature control range: Maintains 37°C optimal temperature for the enviroment
- Dual temperature sensing:
  - Environmental temperature (DHT11)
  - Baby temperature (Dallas sensor)
- Humidity monitoring
- Display refresh rate: 100ms
- Foam construction for thermal insulation

## Safety Features

- Automatic temperature regulation
- Separated electrical component chamber
- Protected observation window
- Airborne bacteria protection through plastic films
- Temperature deviation alerts
- Fail-safe cooling system

## Control System

- Heating Mode (T < 37°C):
  - Heat lamp activated
  - Heat distribution fan enabled
  - Cooling fan disabled
- Cooling Mode (T > 37°C):
  - Heat lamp deactivated
  - Cooling fan activated
  - Heat distribution fan disabled

## Construction

- Main chamber: Insulated foam construction
- Observation window: Transparent plastic sheets
- Separated compartments:
  - Patient (infant) area
  - Electronic components chamber
  - Ventilation system

## Display Information

- Current environmental temperature
- Relative humidity percentage
- Baby's temperature
- System status indicators

## Installation

1. Assemble foam structure according to design
2. Install electronic components in separate chamber
3. Connect sensors and control systems
4. Upload Arduino code
5. Perform system calibration
6. Conduct safety checks

## Pin Configuration

- DHT11 Sensor: Pin 2
- Heat Lamp: Pin 6
- Cooling Fan: Pin 7
- Heating Fan: Pin 10
- Baby Temperature Sensor: Pin 13
- LCD: I2C Interface

## Safety Notes

This is a prototype system for demonstration purposes. Medical certification and additional safety features would be required for clinical use.
