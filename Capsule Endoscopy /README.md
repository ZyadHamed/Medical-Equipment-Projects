
# AI-Enhanced Endoscope System

A smart endoscopy system integrating real-time AI detection for gastrointestinal abnormalities, featuring automated lesion classification and segmentation capabilities.

## Overview

This project implements an intelligent endoscopic system that combines high-resolution imaging with deep learning for real-time detection and classification of gastrointestinal abnormalities, including AVMs, ulcers, and normal tissue.

##Screenshots and videos showcasing the task:
A sample prediction made by the program:
<div align="center">
<table>
  <tr>
    <th>AVM </th> 
    <th>Normal</th> 
  </tr>
  <tr>
    <td><img src="https://github.com/user-attachments/assets/0a3f5803-fd0b-4f00-8676-31643534d25e" alt="Before" width="300"/></td>
    <td><img src="https://github.com/user-attachments/assets/9e73daa7-430a-430b-90d5-8795f5537ea8" alt="After" width="300"/></td>
  </tr>
</table>

</div>

The GUI of the project and predicting a video in realtime:


https://github.com/user-attachments/assets/1ce87879-6a1c-4ad4-bc68-24748b0d79cb


## Key Features

- Real-time video processing and analysis
- AI-powered lesion detection and classification
- Automated segmentation of abnormalities
- High-resolution image processing
- Interactive GUI for video analysis
- YOLO-based segmentation annotations

## Technical Components

### AI Model
- EfficientNet-B0 architecture
- Three-class classification (AVM, Normal, Ulcer)
- Transfer learning from ImageNet
- Early stopping implementation
- Model checkpointing

### Image Processing
- Circular mask application
- White background normalization
- Real-time frame processing
- Ellipse detection and fitting
- YOLO format annotation generation

### User Interface
- Real-time classification display
- Video file selection dialog
- Live prediction visualization
- Interactive controls

## Technical Specifications

### Model Architecture
- Base: EfficientNet-B0
- Output Classes: 3
- Input Size: 224x224
- Normalization: ImageNet standards

### Training Parameters
- Batch Size: 64
- Learning Rate: 1e-4
- Optimizer: Adam
- Loss Function: CrossEntropy
- Early Stopping Patience: 5

### Data Processing
- Image Resolution: 224x224
- Data Augmentation:
  - Horizontal Flip
  - Random Rotation (10°)
  - Normalization

## Installation

```bash
pip install -r requirements.txt
```

## Usage

### Training Mode
```python
python training_code.py
```

### Inference Mode
```python
python GUI.py
```

## Dataset Structure

```
dataset/
├── images/
│   ├── train/
│   └── test/
└── labels/
    ├── train/
    └── test/
```

## Model Training

1. Dataset Preparation
   - Image preprocessing
   - Mask application
   - Annotation generation

2. Training Process
   - Data loading and augmentation
   - Model initialization
   - Training loop execution
   - Validation monitoring

3. Model Evaluation
   - Accuracy assessment
   - Loss monitoring
   - Early stopping implementation

## Inference Pipeline

1. Video Frame Capture
2. Preprocessing
3. AI Analysis
4. Result Visualization
5. Real-time Display

## Performance Metrics

- Training Accuracy
- Validation Accuracy
- Real-time Processing Speed
- Detection Precision

## Requirements

- Python 3.7+
- PyTorch
- OpenCV
- NumPy
- Pandas
- TorchVision
- Scikit-image

## Safety Notes

This system is intended for research and development purposes. Clinical deployment would require additional validation and certification.

## Contributors
Made by https://github.com/Aya423
        https://github.com/ZyadHamed
        https://github.com/YoussefKottb



