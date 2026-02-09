import argparse
import logging
import json

from learn2slither.Environment import IEnvironment, SnakeEnvironment
from learn2slither.Interpreter import IInterpreter, SnakeInterpreter
from learn2slither.Agent import Agent
from learn2slither.Display import IDisplay, WindowedDisplay, ShellDisplay

def get_parser() -> object:
	parser: object = argparse.ArgumentParser(
		prog="learn2slither",
		description="Train an agent to play snake using reinforcement learning."
	)

	parser.add_argument(
		"config",
		default="./includes/configs/default.json",
		type=str
	)
	parser.add_argument(
		"--load",
		type=str
	)
	parser.add_argument(
		"--learn",
		default=False,
		action=argparse.BooleanOptionalAction,
		type=bool
	)
	parser.add_argument(
		"--epochs",
		default=1,
		type=int
	)

	parser.add_argument(
		"--save",
		default="./includes/models/model.json",
		type=str
	)
	parser.add_argument(
		"--visual",
		default=False,
		action=argparse.BooleanOptionalAction,
		type=bool
	)
	parser.add_argument(
		"--visual-type",
		default="shell",
		choices=["shell", "windowed"],
		type=str
	)
	parser.add_argument(
		"--visual-tick",
		default=0.1,
		type=float
	)
	parser.add_argument(
		"--benchmark",
		default=False,
		action=argparse.BooleanOptionalAction,
		type=bool
	)
	parser.add_argument(
		"--debug",
		default=False,
		action=argparse.BooleanOptionalAction,
		type=bool
	)
	return parser.parse_args()

def get_config(config_path: str) -> dict:
	with open(config_path, "r") as file:
		return json.load(file)

def run(config: dict, agent: Agent, parser: object) -> None:
	environment: Environment = None
	agent_learn_map: dict = {True: agent.learn, False: agent.play}
	display: IDisplay = None
	benchmark: dict = {
		"max_duration": 0,
		"mean_duration": 0,
		"max_length": 0,
		"mean_length": 0
	}

	if parser.visual_type:
		if parser.visual_type == "shell":
			display = ShellDisplay(parser.visual_tick)
		else:
			display = WindowedDisplay(parser.visual_tick)
	for epoch in range(parser.epochs):
		logging.debug(f"epoch: {epoch + 1}/{parser.epochs}")
		environment = SnakeEnvironment(config["environment"])
		for _ in agent_learn_map[parser.learn](environment):
			if parser.visual:
				display.show(environment)
		if environment.snake.moves > benchmark["max_duration"]:
			benchmark["max_duration"] = environment.snake.moves
		if environment.snake.length > benchmark["max_length"]:
			benchmark["max_length"] = environment.snake.length
		benchmark["mean_duration"] += environment.snake.moves / parser.epochs
		benchmark["mean_length"] += environment.snake.length / parser.epochs
	if parser.visual:
		display.close()
	if parser.benchmark:
		print("[benchmark]")
		for key, value in benchmark.items():
			print(f"- {key}: {round(value, 2)}")
	if parser.learn and parser.save:
		logging.debug(f"saving agent model to {parser.save}")
		agent.save(parser.save)

def main():
	parser: object = get_parser()
	confif: str = None
	agent: Agent = None

	if parser.debug:
		logging.getLogger().setLevel(logging.DEBUG)
	try:
		config = get_config(parser.config)
		agent = Agent(config["agent"], SnakeInterpreter())
		if parser.load:
			agent.load(parser.load)
		run(config, agent, parser)
	except Exception as error:
		logging.error(error)

if __name__ == "__main__":
	logging.basicConfig(format="[%(asctime)s] [%(levelname)s]: %(message)s", level=logging.INFO)
	main()
