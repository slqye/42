import copy
import random
import json
import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
import seaborn as sns

from dataclasses import dataclass
from datetime import datetime
from enum import Enum
from tqdm import tqdm
from utils import standardize, sigmoid, sigmoid_prime, relu, relu_prime, softmax

class LossEnum(str, Enum):
	"""
	Enumeration of supported loss functions for the neural network.
	"""
	CATEGORICAL_CROSSENTROPY = "categoricalCrossentropy"

class ActivationEnum(str, Enum):
	"""
	Enumeration of supported activation functions for the neural network.
	"""
	SIGMOID = "sigmoid"
	RELU = "relu"

class OptimizationEnum(str, Enum):
	"""
	Enumeration of supported functions optimization for the neural network.
	"""
	NONE = "none"
	MOMENTUM = "momentum"

@dataclass
class TrainConfig:
	"""
	Configuration dataclass for training
	"""
	training: str
	validation: str
	layers: list[int]
	epochs: int
	loss: str
	activation: str
	batch_size: int
	learning_rate: float
	debug: bool
	plot: bool
	save: bool
	seed: int
	loss_stop: float
	history: bool
	optimization: str

class Network:
	"""
	Neural network class responsible for feedforward and backpropagation operations.
	"""

	def __init__(self, dataframe: pd.DataFrame, layers: list[int], loss: str, activation: str, optimization: str) -> None:
		"""
		Initializes the network with random weights and biases based on the input layer sizes and specified architecture.
		"""
		layers.insert(0, dataframe.shape[1] - 1)
		layers.append(2)
		self._weights: list[np.matrix] = [np.matrix(np.random.randn(j, i)) for i, j in zip(layers[:-1], layers[1:])]
		self._bias: list[np.matrix] = [np.matrix(np.random.randn(i)).T for i in layers[1:]]
		self._loss: str = loss
		self._activation: str = activation
		self._optimization: str = optimization
		self._w_velocity = [np.zeros_like(w) for w in self._weights]
		self._b_velocity = [np.zeros_like(b) for b in self._bias]

	def feedforward(self, input: np.ndarray) -> tuple[np.ndarray, np.ndarray]:
		"""
		Performs a forward pass through the network, returning activations and the target vector.
		"""
		target: np.ndarray = np.eye(2)[int(input[1])]
		input: np.ndarray = np.delete(input, 1)
		activations: np.ndarray = [np.matrix(input).T]

		for weights, bias in zip(self._weights[:-1], self._bias[:-1]):
			match self._activation:
				case ActivationEnum.SIGMOID:
					activations.append(sigmoid(np.dot(weights, activations[-1]) + bias))
				case ActivationEnum.RELU:
					activations.append(relu(np.dot(weights, activations[-1]) + bias))
		match self._loss:
			case LossEnum.CATEGORICAL_CROSSENTROPY:
				activations.append(softmax(np.dot(self._weights[-1], activations[-1]) + self._bias[-1]))
		return activations, target

	def backpropagation(self, forward: tuple[np.ndarray, np.ndarray], learning_rate: float) -> None:
		"""
		Updates network weights and biases using backpropagation and the specified learning rate.
		"""
		activations: np.ndarray = [np.matrix(i) for i in forward[0]]
		target: np.matrix = np.matrix(forward[1]).T
		gradient: np.matrix = None
		momentum: float = 0.9

		match self._loss:
			case LossEnum.CATEGORICAL_CROSSENTROPY:
				gradient: np.matrix = np.matrix(activations[-1] - target)
		match self._optimization:
			case OptimizationEnum.NONE:
				self._weights[-1] -= learning_rate * np.dot(gradient, activations[-2].T)
				self._bias[-1] -= learning_rate * gradient
			case OptimizationEnum.MOMENTUM:
				self._w_velocity[-1] = momentum * self._w_velocity[-1] + (1 - momentum) * np.dot(gradient, activations[-2].T)
				self._b_velocity[-1] = momentum * self._b_velocity[-1] + (1 - momentum) * gradient
				self._weights[-1] -= learning_rate * self._w_velocity[-1]
				self._bias[-1] -= learning_rate * self._b_velocity[-1]
		gradient = np.dot(self._weights[-1].T, gradient)
		for layer in reversed(range(len(self._weights) - 1)):
			match self._activation:
				case ActivationEnum.SIGMOID:
					gradient = np.multiply(gradient, sigmoid_prime(activations[layer + 1]))
				case ActivationEnum.RELU:
					gradient = np.multiply(gradient, relu_prime(activations[layer + 1]))
			match self._optimization:
				case OptimizationEnum.NONE:
					self._weights[layer] -= learning_rate * np.dot(gradient, activations[layer].T)
					self._bias[layer] -= learning_rate * gradient
				case OptimizationEnum.MOMENTUM:
					self._w_velocity[layer] = momentum * self._w_velocity[layer] + (1 - momentum) * np.dot(gradient, activations[layer].T)
					self._b_velocity[layer] = momentum * self._b_velocity[layer] + (1 - momentum) * gradient
					self._weights[layer] -= learning_rate * self._w_velocity[layer]
					self._bias[layer] -= learning_rate * self._b_velocity[layer]
			gradient = np.dot(self._weights[layer].T, gradient)

class Model:
	"""
	Model class that manages training, evaluation, and visualization of the neural network.
	"""

	def __init__(self, config: TrainConfig) -> None:
		"""
		Initializes the model with training configuration and prepares the network.
		"""
		self._layers: list[int] = config.layers
		self._epochs: int = config.epochs
		self._loss: str = config.loss
		self._activation: str = config.activation
		self._batch_size: int = config.batch_size
		self._learning_rate: float = config.learning_rate
		self._debug: bool = config.debug
		self._plot: bool = config.plot
		self._loss_stop: float = config.loss_stop
		self._optimization: str = config.optimization
		self._network: Network = None

	def log(self, value: str, end: str = "\n") -> None:
		"""
		Logs a message if debug mode is enabled.
		"""
		if self._debug is True:
			print(value, end=end)

	def compute_loss(self, dataframe: pd.DataFrame) -> float:
		"""
		Computes the average loss of the network over the provided dataset.
		"""
		result: float = 0.0
		epsilon = 1e-15

		for index in range(dataframe.shape[0]):
			forward = self._network.feedforward(np.asarray(dataframe.iloc[index]))
			probability = forward[0][-1][list(forward[1]).index(1)]
			probability = np.clip(probability, epsilon, None)
			result += np.log(probability)
		return float(-result / dataframe.shape[0])

	def compute_accuracy(self, dataframe: pd.DataFrame) -> float:
		"""
		Computes the accuracy of the network over the provided dataset.
		"""
		corrects: int = 0

		for index in range(dataframe.shape[0]):
			forward = self._network.feedforward(np.asarray(dataframe.iloc[index]))
			predicted: list[float] = list([forward[0][-1].flat[0], forward[0][-1].flat[1]])
			observed: list[float] = list(forward[1])
			is_correct: bool = predicted.index(max(predicted)) == observed.index(max(observed))
			corrects += 1 if is_correct else 0
		return corrects / dataframe.shape[0]

	def compute_metrics(self, dataframe: pd.DataFrame) -> list[float]:
		"""
		Computes the metrics of the network over the provided dataset.
		"""
		tp: int = 0
		fp: int = 0
		tn: int = 0
		fn: int = 0
		precision: float = 0
		recall: float = 0
		f1_score: float = 0

		for index in range(dataframe.shape[0]):
			forward = self._network.feedforward(np.asarray(dataframe.iloc[index]))
			predicted: list[float] = list([forward[0][-1].flat[0], forward[0][-1].flat[1]])
			observed: list[float] = list(forward[1])
			holder: tuple[int, int] = (predicted.index(max(predicted)), observed.index(max(observed)))
			match holder:
				case (0, 0):
					tn += 1
				case (0, 1):
					fn += 1
				case (1, 1):
					tp += 1
				case (1, 0):
					fp += 1
		if tp + fp != 0:
			precision = tp / (tp + fp)
		if tp + fn != 0:
			recall = tp / (tp + fn)
		if precision + recall != 0:
			f1_score = 2 * (precision * recall) / (precision + recall)
		return precision, recall, f1_score

	def fit(self, training: pd.DataFrame, validation: pd.DataFrame) -> None:
		"""
		Trains the network using the provided training and validation datasets.
		"""
		forward: tuple[np.ndarray, np.ndarray] = None
		self._network = Network(
			training,
			copy.deepcopy(self._layers),
			self._loss,
			self._activation,
			self._optimization
		)
		items: list[tuple] = list(training.itertuples(index=False))
		losses: list[tuple] = []
		accuracies: list[tuple] = []

		self.log("[debug]: training - validation")
		self.log(f"[shapes]: {training.shape} - {validation.shape}")
		for epoch in range(self._epochs):
			items_batch: np.ndarray = np.asarray(random.sample(items, k=self._batch_size))
			for item in items_batch:
				forward = self._network.feedforward(item)
				self._network.backpropagation(forward, self._learning_rate)
			if self._plot is True:
				losses.append((self.compute_loss(training), self.compute_loss(validation)))
				accuracies.append((self.compute_accuracy(training), self.compute_accuracy(validation)))
			self.log(f"[{(epoch + 1):0{len(str(self._epochs))}d}/{self._epochs}]:", " ")
			self.log(f"{(self.compute_loss(training) if self._debug else 0):5.5f} -", end=" ")
			self.log(f"{(self.compute_loss(validation) if self._debug else 0):5.5f}", end="\r")
			if self._loss_stop != 0:
				if self.compute_loss(training) <= self._loss_stop:
					break
		self.log("\n", end="")
		self.log(f"[metrics]: {self.compute_metrics(training)}")
		self.log(f"[metrics]: {self.compute_metrics(validation)}")
		if self._plot is True:
			self.plot(losses, accuracies)

	def plot(self, losses: list[tuple], accuracies: list[tuple]) -> None:
		"""
		Plots training and validation loss and accuracy over epochs.
		"""
		sns.lineplot([x[0] for x in losses], label="training")
		sns.lineplot([x[1] for x in losses], label="validation")
		plt.title("Training and Validation Loss")
		plt.xlabel("Epoch")
		plt.ylabel("Loss")
		plt.legend()
		plt.show()
		plt.close()
		sns.lineplot([x[0] for x in accuracies], label="training")
		sns.lineplot([x[1] for x in accuracies], label="validation")
		plt.title("Training and Validation accuracies")
		plt.xlabel("Epoch")
		plt.ylabel("Accuracy")
		plt.legend()
		plt.show()

	def save_hyperparameters(self) -> None:
		"""
		Saves the trained network weights and biases to a file.
		"""
		self.log("[save]: hyperparameters")
		np.savez(
			"training.npz",
			weights=np.array(self._network._weights, dtype=object),
			biases=np.array(self._network._bias, dtype=object)
		)

	def save_history(self, training: pd.DataFrame, validation: pd.DataFrame) -> None:
		"""
		Saves the trained network weights and biases to a file.
		"""
		self.log("[save]: history")
		t_metrics: list[float] = self.compute_metrics(training)
		v_metrics: list[float] = self.compute_metrics(validation)
		data = {
			"timestamp": datetime.now().isoformat(),
			"config": {
				"layers": self._layers,
				"epochs": self._epochs,
				"loss": self._loss,
				"activation": self._activation,
				"batch_size": self._batch_size,
				"learning_rate": self._learning_rate,
				"debug": self._debug,
				"plot": self._plot,
				"loss_stop": self._loss_stop,
				"optimization": self._optimization
			},
			"metrics": {
				"training": {
					"loss": self.compute_loss(training),
					"accuracy": self.compute_accuracy(training),
					"precision": t_metrics[0],
					"recall": t_metrics[1],
					"f1_score": t_metrics[2]
				},
				"validation": {
					"loss": self.compute_loss(validation),
					"accuracy": self.compute_accuracy(validation),
					"precision": v_metrics[0],
					"recall": v_metrics[1],
					"f1_score": v_metrics[2]
				}
			}
		}
		with open("history.jsonl", "a") as file:
			file.write(json.dumps(data) + "\n")

def perform_train(config: TrainConfig) -> None:
	"""
	Trains a neural network model using the specified dataset and parameters.
	"""
	training: pd.DataFrame = pd.read_csv(config.training, header=None)
	validation: pd.DataFrame = pd.read_csv(config.validation, header=None)
	training[1] = training[1].map({"B": 0, "M": 1})
	validation[1] = validation[1].map({"B": 0, "M": 1})
	training = training.dropna()
	validation = validation.dropna()

	if config.seed != -1:
		random.seed(config.seed)
		np.random.seed(config.seed)
	if config.batch_size == -1:
		config.batch_size = training.shape[0]
	standardize(training, 1)
	standardize(validation, 1)
	model: Model = Model(config)
	model.fit(training, validation)
	if config.save is True:
		model.save_hyperparameters()
	if config.history is True:
		model.save_history(training, validation)
