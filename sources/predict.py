import numpy as np
import pandas as pd

from dataclasses import dataclass
from utils import standardize
from train import Network

@dataclass
class PredictConfig:
	"""
	Configuration dataclass for prediction.
	"""
	dataset: str
	hyperparameters: str
	activation: str
	loss: str
	output: str

def evaluate(predictions, target):
	"""
	Computes the categorical cross-entropy loss between predictions and target labels.
	"""
	length: int = len(predictions)
	result: float = 0

	for p, t in zip(predictions, target):
		p = np.clip(p, 1e-15, 1 - 1e-15)
		result += - (t * np.log(p) + (1 - t) * np.log(1 - p))
	return float(result / length)

def save_predictions(predictions: list, output: str) -> None:
	"""
	Saves model predictions to a CSV file, mapping numeric predictions to 'B' or 'M' labels.
	"""
	with open(output, "w") as file:
		file.write("index,prediction\n")
		for index, prediction in enumerate(predictions):
			prediction: float = float(list(prediction).index(max(prediction)))
			file.write(f"{index},{'B' if prediction == 0 else 'M'}\n")

def perform_predict(config: PredictConfig) -> None:
	"""
	Predicts using the trained model weights on the provided dataset.
	"""
	dataset: pd.DataFrame = pd.read_csv(config.dataset, header=None)
	dataset[1] = dataset[1].map({"B": 0, "M": 1})
	dataset = dataset.dropna()
	standardize(dataset, 1)
	hyperparameters = np.load(config.hyperparameters, allow_pickle=True)
	weights = hyperparameters["weights"]
	biases = hyperparameters["biases"]
	network = Network.__new__(Network)
	network._weights = weights
	network._bias = biases
	network._activation = config.activation
	network._loss = config.loss
	result = [[], []]
	for index in range(dataset.shape[0]):
		forward = network.feedforward(np.array(dataset.iloc[index]))
		result[0].append((forward[0][-1]))
		result[1].append((forward[1]))
	save_predictions(result[0], config.output)
	print(f"[loss]: {evaluate(result[0], result[1]):5.5f}")
