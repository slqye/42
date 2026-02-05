import logging
import json

from learn2slither.environment import Environment
from learn2slither.interpreter import Interpreter
from learn2slither.agent import Agent

def compute_config(path: str) -> dict:
	with open(path, "r") as file:
		return json.load(file)

def main(path: str = "./includes/config.json", epochs: int = 1000):
	config: dict = compute_config(path)
	environment: Environment = Environment(config["environment"])

	print(environment)
	environment.action(0)
	print(environment)

if __name__ == "__main__":
	logging.basicConfig(format="[%(asctime)s] [%(levelname)s]: %(message)s", level=logging.INFO)
	main()
