from r_learn.environment import SnakeEnvironment
from r_learn.interpreter import SnakeInterpreter
from r_learn.agent import SnakeAgent

def main():
	environment: SnakeEnvironment = SnakeEnvironment(10)
	interpreter: SnakeInterpreter = SnakeInterpreter(environment)
	agent: SnakeAgent = SnakeAgent(interpreter)

	print(environment)

if __name__ == "__main__":
	main()
