import logging
import json

from learn2slither.environment import Environment
from learn2slither.interpreter import Interpreter, SnakeInterpreter
from learn2slither.agent import Agent

def compute_config(config_path: str) -> dict:
	with open(config_path, "r") as file:
		return json.load(file)

def main(config_path: str = "./includes/config_default.json"):
	config: dict = compute_config(config_path)
	agent: Agent = Agent(config["agent"], SnakeInterpreter())
	environment: Environment = None

	for epoch in range(config["agent"]["epochs"]):
		logging.info(f"epoch {epoch + 1}/{config['agent']['epochs']}")
		environment = Environment(config["environment"])
		for _ in agent.learn(environment):
			continue

if __name__ == "__main__":
	logging.basicConfig(format="[%(asctime)s] [%(levelname)s]: %(message)s", level=logging.INFO)
	main()
