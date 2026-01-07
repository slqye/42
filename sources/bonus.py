import sys
import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
import seaborn as sns

DATASET_PATH = "includes/data.csv"

def get_training_output() -> tuple[float, float]:
	"""
	Reads slope and intercept from "training.out".
	"""
	try:
		with open("training.out", "r", encoding="utf-8") as file:
			lines: list[str] = file.readlines()
			slope: float = float(lines[0])
			intersect: float = float(lines[1])
			return (slope, intersect)
	except FileNotFoundError:
		return (0, 0)
	except Exception as error:
		print("Error:", error, file=sys.stderr)
		sys.exit(1)

def compute_rmse(dataset: pd.DataFrame, t0: float, t1: float) -> float:
	"""
	Compute linear regression RMSE (root mean squared error).
	"""
	mse_array: list[float] = [
		(x["price"] - (t1 * x["km"] + t0))**2
		for _, x in dataset.iterrows()
	]
	return (1 / dataset.shape[0] * sum(mse_array))**0.5

def plot_model(dataset: pd.DataFrame, t0: float, t1: float, rmse: float) -> None:
	"""
	Plots the dataset and the linear regression model with RMSE.
	"""
	sns.set_theme()
	sns.scatterplot(
		data=dataset,
		x="km",
		y="price",
		label="dataset"
	)
	x_line = np.linspace(min(dataset["km"]), max(dataset["km"]), 10)
	y_line = t1 * x_line + t0
	plt.plot(
		x_line,
		y_line,
		color="red",
		label=f"linear regression\nrmse = {rmse:.2f}"
	)
	plt.title("Linear regression model")
	plt.legend()
	plt.show()

def main():
	"""
	Loads the dataset, evaluates the regression model, and plots it with the computed RMSE.
	"""
	try:
		dataset: pd.DataFrame = pd.read_csv(DATASET_PATH)
		function: tuple[float, float] = get_training_output()
		rmse: float = compute_rmse(dataset, function[1], function[0])
		plot_model(dataset, function[1], function[0], rmse)
	except Exception as error:
		print("Error:", error, file=sys.stderr)
		sys.exit(1)


if __name__ == "__main__":
	main()
