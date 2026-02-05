import logging
import json
import time

from learn2slither.environment import Environment, SnakeEnvironment
from learn2slither.interpreter import Interpreter, SnakeInterpreter
from learn2slither.agent import Agent, SnakeAgent
from learn2slither import simulation

EPOCHS = 1000

def compute_config(config_path: str) -> dict:
	with open(config_path, "r") as file:
		return json.load(file)

def main(config_path: str = "./includes/config_default.json"):
	config: dict = compute_config(config_path)
	agent: SnakeAgent = SnakeAgent(config["agent"], SnakeInterpreter())
	environment: SnakeEnvironment = None

	agent.load("model.json")
	for epoch in range(EPOCHS):
		logging.info(f"epoch {epoch + 1}/{EPOCHS}")
		environment = SnakeEnvironment(config["environment"])
		for _ in agent.learn(environment):
			continue
	agent.save("model.json")
	environment = SnakeEnvironment(config["environment"])
	simulation.shell(agent, environment, 0.1)

if __name__ == "__main__":
	logging.basicConfig(format="[%(asctime)s] [%(levelname)s]: %(message)s", level=logging.INFO)
	main()
