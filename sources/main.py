import logging

from r_learn.environment import SnakeEnvironment
from r_learn.interpreter import SnakeInterpreter
from r_learn.agent import SnakeAgent

logging.basicConfig(format="[%(asctime)s] [%(levelname)s]: %(message)s", level=logging.DEBUG)

def main():
	environment: SnakeEnvironment = SnakeEnvironment(10)
	interpreter: SnakeInterpreter = SnakeInterpreter(environment)
	agent: SnakeAgent = SnakeAgent(interpreter)
	moves: dict = {
		1: environment.ACTION_LEFT,
		2: environment.ACTION_RIGHT,
		3: environment.ACTION_UP,
		4: environment.ACTION_DOWN,
	}

	while environment.running:
		print(environment)
		action: int = int(input("move: "))
		if action == 0: break
		environment.action(moves[action])

if __name__ == "__main__":
	main()
