import random

from dataclasses import dataclass

@dataclass
class SplitConfig:
	"""
	Configuration dataclass for split.
	"""
	dataset: str
	ratio: float
	seed: int

def perform_split(config: SplitConfig) -> None:
	"""
	Splits the dataset into training and validation CSVs.
	"""
	outputs: tuple[str, str] = ("includes/training.csv", "includes/validation.csv")
	lines: list[str] = []

	if config.seed != -1:
		random.seed(config.seed)
	with open(config.dataset, "r") as file:
		lines = [line.strip() for line in file if line.strip()]
	random.shuffle(lines)
	index = int(len(lines) * config.ratio)
	training: list[str] = lines[:index]
	validation: list[str] = lines[index:]
	with open(outputs[0], "w") as file:
		file.write("\n".join(training))
	with open(outputs[1], "w") as file:
		file.write("\n".join(validation))
