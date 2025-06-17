# ECG Visualizer

A real-time ECG (Electrocardiogram) visualization and analysis application built with C# and WPF, utilizing Arduino for data acquisition.

## Screenshots and videos showcasing the task:
ECG signal displaying on the application and a demonstration of features:


## Features

- Real-time ECG signal visualization using ScottPlot
- Heart rate calculation and monitoring
- Multiple signal filtering options:
  - Low Pass Filter
  - High Pass Filter
  - Butterworth Filter
  - Moving Average Filter
- QRS wave inversion capability for simulating a disease and visualizing it through the ECG signal
- Serial port communication with Arduino ECG sensor

## Requirements

- .NET Framework
- Arduino board with ECG sensor
- ScottPlot.WPF library
- Serial port connection (default: COM13)

## Setup

1. Connect the Arduino board with the ECG sensor
2. Configure the correct COM port in the application (default is COM13)
3. Build and run the application
4. Ensure proper connection between the ECG sensor and the subject

## Usage

The application provides a user interface with the following controls:

- Filter toggles:
  - Low Pass Filter
  - High Pass Filter
  - Butterworth Filter
  - Moving Average Filter
- QRS Inversion toggle
- Real-time heart rate display
- Error percentage calculation

## Signal Processing

The application implements various digital filters for signal processing:

- Low Pass Filter: Reduces high-frequency noise
- High Pass Filter: Removes baseline drift
- Butterworth Filter: Provides optimal frequency response
- Moving Average Filter: Smooths the signal

## Heart Rate Calculation

- Detects QRS peaks in real-time
- Calculates average heart rate using R-R intervals
- Maintains a rolling average of recent measurements
- Validates heart rate within physiological range (30-160 BPM)

## Error Handling

- Robust error handling for serial communication
- Data validation for heart rate calculations
- Graceful application shutdown
- Thread-safe data processing

## Technical Details

- Sampling Rate: 115200 baud
- Display Buffer: 300 samples
- Heart Rate Average Window: 10 samples
- Updates at 60 FPS
