import sys
import os
import typer
import torch
import torch.nn as nn
import torch.optim as optim

from torch.utils.data import DataLoader
from torchvision import datasets, transforms, models
from tqdm import tqdm

BATCH_SIZE = 200
LEARNING_RATE = 1e-4
DATASETS = ("training", "validation")


def create_model(directory: str) -> (object, tuple):
    """
    Return a new model based on ResNet18 model's weights.
    """
    transform: object = None
    model: object = None
    g_datasets: list = []
    g_loaders: list = []
    class_names: list = []

    transform = transforms.Compose([
        transforms.ToTensor(),
        transforms.Normalize((0.485, 0.456, 0.406), (0.229, 0.224, 0.225))
    ])
    for dataset in DATASETS:
        g_datasets.append(
            datasets.ImageFolder(
                os.path.join(directory, dataset),
                transform=transform
            )
        )
    for index, dataset in enumerate(g_datasets):
        g_loaders.append(
            DataLoader(
                dataset,
                batch_size=BATCH_SIZE,
                shuffle=True if index == 0 else False
            )
        )
    class_names = g_datasets[0].classes
    model = models.resnet18(weights=models.ResNet18_Weights.DEFAULT)
    model.fc = nn.Linear(model.fc.in_features, len(class_names))
    return (model, g_loaders)


def train_model(
    model: object,
    training_loader: object,
    device: str,
    epochs: int = 10
) -> None:
    """
    Acctualy train the model.
    """
    optimizer: object = None
    criterion: object = None
    loss_holder: float = 0.0

    optimizer = optim.Adam(model.parameters(), lr=LEARNING_RATE)
    criterion = nn.CrossEntropyLoss()
    model.to(device)
    for epoch in range(epochs):
        model.train()
        loss_holder = 0.0
        for inputs, labels in tqdm(training_loader):
            inputs, labels = inputs.to(device), labels.to(device)
            optimizer.zero_grad()
            outputs = model(inputs)
            loss = criterion(outputs, labels)
            loss.backward()
            optimizer.step()
            loss_holder += loss.item()
        print(f"[{epoch+1}/{epochs}]: {loss_holder/len(training_loader):.5f}")


def compute_model_accurary(
    model: object,
    validation_loader: object,
    device: str
) -> None:
    """
    Compute and display model accuray.
    """
    correct: int = 0
    total: int = 0

    model.eval()
    with torch.no_grad():
        for inputs, labels in validation_loader:
            inputs, labels = inputs.to(device), labels.to(device)
            outputs = model(inputs)
            _, predicted = torch.max(outputs, 1)
            total += labels.size(0)
            correct += (predicted == labels).sum().item()
    print(f"[Accuracy]: {100 * correct / total:.2f}%")


def main(directory: str) -> None:
    """
    Training entry point.
    """
    model: object = None
    loaders: object = None
    device: str = ""

    device = torch.device("cuda" if torch.cuda.is_available() else "cpu")
    print("[model]: creating")
    model, loaders = create_model(directory)
    print("[model]: training")
    train_model(model, loaders[0], device, 1)
    print("[model]: accurary")
    compute_model_accurary(model, loaders[1], device)
    print("[model]: saving")
    torch.save(model.state_dict(), "model.pth")


if __name__ == "__main__":
    try:
        typer.run(main)
    except Exception as error:
        print(f"error: {error}", file=sys.stderr)
