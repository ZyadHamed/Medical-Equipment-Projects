# ECG Visualizer

A real-time ECG (Electrocardiogram) visualization and analysis application built with C# and WPF, utilizing Arduino for data acquisition.

## Screenshots and videos showcasing the task:
Sensor Setup:
![SensorSetup](https://github.com/user-attachments/assets/3b461600-ed48-42bc-bfcb-056e4e2ed569)

Live sensor readings:


https://github.com/user-attachments/assets/eebedfc4-44e1-4db6-9b9d-b493417dccce


Corrosponding ECG signal displaying on the application and a demonstration of features:


https://github.com/user-attachments/assets/14fd8a21-9b0d-44bf-af7c-76c50629ed68


## Features

### Real-time Monitoring
- Live ECG signal visualization using ScottPlot
- Heart rate calculation and monitoring
- QRS wave inversion capability
- Thread-safe data processing

### Signal Processing
#### Digital Filters
- Low Pass Filter: Reduces high-frequency noise
- High Pass Filter: Removes baseline drift
- Butterworth Filter: Provides optimal frequency response
- Moving Average Filter: Smooths the signal
- Notch Filter: Removes 50Hz power line interference

#### Frequency Analysis
- Fast Fourier Transform (FFT) implementation
- Frequency spectrum visualization
- Power line noise detection
- Signal quality assessment

### Data Analysis
- Heart rate calculation using R-R intervals
- Rolling average measurements
- Physiological range validation (30-160 BPM)
- Error percentage calculation

## Technical Implementation

### Hardware Interface
- Arduino-based ECG sensor
- Serial communication (115200 baud)
- Configurable COM port selection

### Signal Processing Details
- Sampling Rate: 1000 Hz
- Display Buffer: 300 samples
- Heart Rate Window: 10 samples
- GUI Updates: 60 FPS
- Notch Filter Parameters:
  - Frequency: 50 Hz
  - Quality Factor: 30

### Analysis Tools
- Time domain visualization
- Frequency domain analysis
- Power spectrum computation
- Noise filtering demonstration

## Requirements

### Software
- .NET Framework
- Python 3.x
- ScottPlot.WPF library
- SciPy
- NumPy
- Matplotlib

### Hardware
- Arduino board
- ECG sensor
- Serial port connection

## Setup and Installation

1. Hardware Setup
   - Connect Arduino with ECG sensor
   - Configure COM port (default: COM13)

2. Software Installation
   ```bash
   pip install scipy numpy matplotlib
   ```

3. Application Launch
   - Build and run the C# application
   - Run Python scripts for advanced analysis

## Usage

### Real-time Monitoring
- Launch the WPF application
- Select desired filters
- Monitor heart rate and ECG trace

### Signal Analysis
- Load ECG data files in the ecg-filteration-task.ipynb file (.mat format)
- Run FFT analysis
- Visualize frequency components
- Apply noise reduction

## Data Visualization

### Available Plots
- Real-time ECG trace
- Frequency spectrum
- Before/after noise filtering
- Heart rate trends

### Analysis Features
- Time domain visualization
- Frequency domain analysis
- Noise comparison
- Filter performance evaluation

## Error Handling

- Serial communication management
- Data validation
- Graceful shutdown procedures
- Real-time error reporting

## Technical Documentation

### Signal Processing Pipeline
1. Raw signal acquisition
2. Noise filtering
3. QRS detection
4. Heart rate calculation
5. Real-time visualization

### Filter Specifications
- Notch Filter: 50Hz noise removal
- Various digital filters for signal cleaning
- Customizable filter parameters

## Acknowledgments

- Signal processing libraries
For detailed implementation examples and code samples, please refer to the source files in the repository.
