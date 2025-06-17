
import cv2
import torch
import numpy as np
from tkinter import Tk, Button, filedialog
from torchvision import transforms, models
import torch.nn as nn

# Set up model
device = torch.device('cuda' if torch.cuda.is_available() else 'cpu')
model = models.efficientnet_b0(pretrained=False)
model.classifier[1] = nn.Linear(model.classifier[1].in_features, 3)
model.load_state_dict(torch.load("best_model.pth", map_location=device))
model = model.to(device)
model.eval()

# Label map
label_map = {0: "AVM", 1: "Normal", 2: "Ulcer"}

# Define preprocessing
val_transform = transforms.Compose([
    transforms.ToPILImage(),
    transforms.Resize((224, 224)),
    transforms.ToTensor(),
    transforms.Normalize([0.485, 0.456, 0.406],
                         [0.229, 0.224, 0.225])
])

# Video classification function
def classify_video():
    video_path = filedialog.askopenfilename(title="Select Video File",
                                            filetypes=[("Video files", "*.mp4 *.avi *.mov")])
    if not video_path:
        return

    cap = cv2.VideoCapture(video_path)

    while cap.isOpened():
        ret, frame = cap.read()
        if not ret:
            break

        # Preprocess frame
        height, width = frame.shape[:2]
        mask = np.zeros((height, width), dtype=np.uint8)
        center = (width // 2, height // 2)
        radius = min(center[0], center[1]) + 17
        cv2.circle(mask, center, radius, 255, -1)
        masked = cv2.bitwise_and(frame, frame, mask=mask)
        white_bg = np.ones_like(frame, dtype=np.uint8) * 255
        processed = np.where(mask[:, :, np.newaxis] == 255, masked, white_bg)
        processed = cv2.cvtColor(processed, cv2.COLOR_BGR2RGB)
        transformed = val_transform(processed).unsqueeze(0).to(device)

        # Predict
        with torch.no_grad():
            outputs = model(transformed)
            pred = torch.argmax(outputs, 1).item()
            label = label_map[pred]

        # Draw prediction on frame
        display_frame = cv2.putText(frame.copy(), f"Prediction: {label}",
                                    (10, 30), cv2.FONT_HERSHEY_SIMPLEX,
                                    1, (0, 0, 255), 2, cv2.LINE_AA)

        # Show video
        cv2.imshow("Video Classification", display_frame)
        if cv2.waitKey(30) & 0xFF == ord('q'):
            break

    cap.release()
    cv2.destroyAllWindows()

# GUI setup
root = Tk()
root.title("Video Frame Classifier")
root.geometry("300x150")

btn = Button(root, text="Select and Classify Video", command=classify_video, font=("Helvetica", 14))
btn.pack(pady=40)

root.mainloop()
