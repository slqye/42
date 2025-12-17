import sys
import typer
import torch
import torch.nn as nn
import tkinter as tk
import cv2
import Transformation

from PIL import Image, ImageTk
from torchvision import transforms, models

CLASS_NAMES = [
    "Apple_Black_rot",
    "Apple_healthy",
    "Apple_rust",
    "Apple_scab",
    "Grape_Black_rot",
    "Grape_Esca",
    "Grape_healthy",
    "Grape_spot"
]


def model_predict(model: object, image: str) -> str:
    """
    Compute and display model accuray.
    """
    with torch.no_grad():
        outputs = model(image)
        _, predicted = torch.max(outputs, 1)
        return CLASS_NAMES[predicted.item()]


def display_prediction(image: str, prediction: str) -> None:
    """
    Prediction display with base and transformed image.
    """
    root: object = None
    frame: object = None
    transformator: object = None
    base_image: object = None
    transformed_image: object = None
    rgb: list = []

    root = tk.Tk()
    root.configure(bg="black")
    root.title("Leaffliction")
    transformator = Transformation.Transformator(image)
    rgb.append(cv2.cvtColor(transformator._image, cv2.COLOR_BGR2RGB))
    rgb.append(cv2.cvtColor(transformator.compute.masked(), cv2.COLOR_BGR2RGB))
    base_image = ImageTk.PhotoImage(Image.fromarray(rgb[0]))
    transformed_image = ImageTk.PhotoImage(Image.fromarray(rgb[1]))
    frame = tk.Frame(root, bg="black")
    frame.pack(padx=10, pady=10)
    tk.Label(frame, image=base_image).pack(side="left", padx=10)
    tk.Label(frame, image=transformed_image).pack(side="left", padx=10)
    tk.Label(
        root,
        text=f"prediction: {prediction.lower()}",
        font=("Helvetica", 18, "bold"),
        fg="white",
        bg="black"
    ).pack(pady=10)
    root.mainloop()


def main(model_path: str, image_path: str) -> None:
    """
    Predict entry point.
    """
    model: object = None
    transform: object = None
    device: str = ""
    image_tensor: object = None

    model = models.resnet18(weights=models.ResNet18_Weights.DEFAULT)
    model.fc = nn.Linear(model.fc.in_features, 8)
    model.load_state_dict(torch.load(model_path))
    model.eval()
    transform = transforms.Compose([
        transforms.ToTensor(),
        transforms.Normalize((0.485, 0.456, 0.406), (0.229, 0.224, 0.225))
    ])
    device = next(model.parameters()).device
    image_tensor = transform(
        Image.open(image_path).convert("RGB")
    ).unsqueeze(0)
    image_tensor = image_tensor.to(device)
    display_prediction(image_path, model_predict(model, image_tensor))


if __name__ == "__main__":
    try:
        typer.run(main)
    except Exception as error:
        print(f"error: {error}", file=sys.stderr)
