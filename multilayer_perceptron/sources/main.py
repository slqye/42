import sys
import typing
import typer
import numpy as np

from typing_extensions import Annotated
from split import SplitConfig, perform_split
from train import LossEnum, ActivationEnum, OptimizationEnum, TrainConfig, perform_train
from predict import PredictConfig, perform_predict

app = typer.Typer()

@app.command()
def split(
	dataset: Annotated[str, typer.Argument()],
	ratio: Annotated[float, typer.Option()] = 0.8,
	seed: Annotated[int, typer.Option()] = -1,
) -> None:
	"""
	Splits the dataset into training and validation CSVs.
	"""
	try:
		config: SplitConfig = SplitConfig(
			dataset=dataset,
			ratio=ratio,
			seed=seed
		)
		perform_split(config)
	except Exception as error:
		print("error:", error, file=sys.stderr)

@app.command()
def train(
	training: Annotated[str, typer.Argument()] = "includes/training.csv",
	validation: Annotated[str, typer.Argument()] = "includes/validation.csv",
	layers: Annotated[typing.Optional[list[int]], typer.Option("--layer")] = [24, 24],
	epochs: Annotated[int, typer.Option] = 1000,
	batch_size: Annotated[int, typer.Option] = -1,
	seed: Annotated[int, typer.Option] = -1,
	loss_stop: Annotated[float, typer.Option] = 0,
	learning_rate: Annotated[float, typer.Option] = 0.001,
	loss: Annotated[LossEnum, typer.Option] = LossEnum.CATEGORICAL_CROSSENTROPY,
	activation: Annotated[ActivationEnum, typer.Option] = ActivationEnum.SIGMOID,
	optimization: Annotated[OptimizationEnum, typer.Option] = OptimizationEnum.NONE,
	debug: Annotated[bool, typer.Option] = False,
	plot: Annotated[bool, typer.Option] = False,
	save: Annotated[bool, typer.Option] = True,
	history: Annotated[bool, typer.Option] = False
) -> None:
	"""
	Trains a neural network model using the specified dataset and parameters.
	"""
	try:
		config: TrainConfig = TrainConfig(
			training=training,
			validation=validation,
			layers=layers,
			epochs=epochs,
			loss=loss,
			activation=activation,
			batch_size=batch_size,
			learning_rate=learning_rate,
			debug=debug,
			plot=plot,
			save=save,
			seed=seed,
			loss_stop=loss_stop,
			history=history,
			optimization=optimization
		)
		perform_train(config)
	except Exception as error:
		print("error:", error, file=sys.stderr)

@app.command()
def predict(
	dataset: Annotated[str, typer.Argument()],
	hyperparameters: Annotated[str, typer.Argument()] = "training.npz",
	activation: Annotated[ActivationEnum, typer.Option] = ActivationEnum.SIGMOID,
	loss: Annotated[LossEnum, typer.Option] = LossEnum.CATEGORICAL_CROSSENTROPY,
	output: Annotated[str, typer.Option] = "predictions.csv"
) -> None:
	"""
	Predicts using the trained model weights on the provided dataset.
	"""
	try:
		config: PredictConfig = PredictConfig(
			dataset=dataset,
			hyperparameters=hyperparameters,
			activation=activation,
			loss=loss,
			output=output
		)
		perform_predict(config)
	except Exception as error:
		print("error:", error, file=sys.stderr)

if __name__ == "__main__":
	np.seterr(all='raise')
	app()
