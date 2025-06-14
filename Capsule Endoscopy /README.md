# AI Model to Classify videos and images (Normal . AVM , Ulcer)
# 🧠 Video Frame Classifier

This project is a simple desktop application that performs **real-time frame-by-frame classification** on videos using a deep learning model based on **EfficientNet-B0**. The model predicts one of three medical conditions from each frame: **AVM**, **Normal**, or **Ulcer**.
---
## 🚀 Features

- Loads and plays any `.mp4`, `.avi`, or `.mov` video file.
- Automatically classifies each frame in real time using a pretrained PyTorch model.
- Displays the predicted label on the video as it plays.
- Uses a circular mask on the frame to focus prediction on the central region.
---
## 🧰 Tech Stack

- **Python 3**
- **PyTorch**
- **Torchvision**
- **OpenCV**
- **Tkinter** (for GUI)
---
## 📦 Installation

1. Clone the repository:
2. Install the required libraries
3. Make sure to place your trained model file (`best_model.pth`) in the root directory of the project.
---
## 🖥️ Usage

Run the app with:
A window will appear. Click the button to select a video file, and the classification will begin automatically. Press `q` to quit the video.

## 🧠 Model Details

The model used is `EfficientNet-B0`, fine-tuned to classify frames into:

- `AVM`  
- `Normal`  
- `Ulcer`

It expects RGB images of size 224×224 with standard ImageNet normalization.


## 📝 License

This project is licensed under the [MIT License](LICENSE).

## 🙋‍♀️ Author

Made by https://github.com/Aya423
        https://github.com/ZyadHamed
        https://github.com/YoussefKottb



