import logging

from r_learn.environment import SnakeEnvironment
from r_learn.interpreter import SnakeInterpreter
from r_learn.agent import SnakeAgent

logging.basicConfig(format="[%(asctime)s] [%(levelname)s]: %(message)s", level=logging.INFO)

EPOCHS = 10000

def main():
	q_table_holder: dict = None

	for epoch in range(EPOCHS):
		environment: SnakeEnvironment = SnakeEnvironment(10)
		interpreter: SnakeInterpreter = SnakeInterpreter(environment)
		agent: SnakeAgent = SnakeAgent(interpreter)
		if q_table_holder is not None:
			agent._q_table = q_table_holder
		moves: int = 0
		while environment.running:
			agent.perform_action(environment)
			agent.mesure_reward(environment)
			agent.update_q_table(environment)
			moves += 1
		logging.info(f"[{epoch + 1}/{EPOCHS}]: {environment.get_snake_length()}, {moves}")
		q_table_holder = agent._q_table


if __name__ == "__main__":
	main()
