import pandas as pd
import numpy as np

def standardize(dataframe: pd.DataFrame, target: str) -> None:
	"""
	Standardizes all features in the dataframe except the target column using mean and standard deviation.
	"""
	features = [x for x in dataframe.columns if x != target]
	df_features = dataframe[features]
	dataframe[features] = (df_features - df_features.mean()) / df_features.std()

def sigmoid(x: np.matrix) -> np.matrix:
	"""
	Applies the sigmoid activation function element-wise to the input matrix.
	"""
	result = np.zeros((x.shape[0], x.shape[1]))
	for i in range(x.shape[1]):
		if x[0, i] >= 0:
			result[0, i] = 1 / (1 + np.exp(-x[0, i]))
		else:
			result[0, i] = np.exp(x[0, i]) / (1 + np.exp(x[0, i]))
	return result

def sigmoid_prime(x: np.matrix) -> np.matrix:
	"""
	Computes the derivative of the sigmoid function for the input matrix.
	"""
	return (np.multiply(x, (1 - x)))

def relu(x: np.matrix) -> np.matrix:
	"""
	Applies the ReLU activation function element-wise to the input matrix, with a cap at 1000.
	"""
	return np.maximum(0, x)

def relu_prime(x: np.matrix) -> np.matrix:
	"""
	Computes the derivative of the ReLU function for the input matrix.
	"""
	return (x > 0).astype(int)

def softmax(x: np.ndarray) -> np.ndarray:
	"""
	Applies the softmax function to the input array for probability distribution.
	"""
	return (x_exps := np.exp(x)) / sum(x_exps)
