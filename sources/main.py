import argparse
import logging
import json

from learn2slither.Environment import IEnvironment, SnakeEnvironment
from learn2slither.Interpreter import IInterpreter, SnakeInterpreter
from learn2slither.Agent import Agent
from learn2slither import simulation

def get_parser() -> object:
	parser: object = argparse.ArgumentParser(
		prog="learn2slither",
		description="Train an agent to play snake using reinforcement learning."
	)

	parser.add_argument(
		"--config",
		default="./includes/configs/default.json",
		metavar="path",
		help="path to a configuration file"
	)
	parser.add_argument(
		"--model",
		metavar="path",
		help="intialise the agent with a custom model"
	)
	parser.add_argument(
		"--train",
		nargs=2,
		metavar=("epochs", "path"),
		help="train an agent with a number of epoch and a saving_path"
	)
	parser.add_argument(
		"--display",
		default="shell",
		choices=["shell", "windowed", "none"],
		help="display a simulation of the agent"
	)
	return parser.parse_args()

def get_config(config_path: str) -> dict:
	with open(config_path, "r") as file:
		return json.load(file)

def train(config: dict, agent: Agent, epochs: int, saving_path: str) -> None:
	logging.info(f"training model with {epochs} epochs")
	for epoch in range(epochs):
		logging.debug(f"training: {epoch}/{epochs}")
		for _ in agent.learn(SnakeEnvironment(config["environment"])):
			continue
	logging.info(f"saving model to {saving_path}")
	agent.save(saving_path)

def main():
	parser: object = get_parser()
	confif: str = None
	agent: Agent = None

	try:
		config = get_config(parser.config)
		agent = Agent(config["agent"], SnakeInterpreter())
		if parser.model:
			agent.load(parser.model)
		if parser.train:
			train(config, agent, int(parser.train[0]), parser.train[1])
		match parser.display:
			case "shell":
				simulation.shell(agent, SnakeEnvironment(config["environment"]), 0.1)
			case "none":
				return
	except Exception as error:
		logging.error(error)

if __name__ == "__main__":
	logging.basicConfig(format="[%(asctime)s] [%(levelname)s]: %(message)s", level=logging.INFO)
	main()
