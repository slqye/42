import json
import random

class Agent:
	def __init__(self, config: dict, interpreter: object) -> None:
		self.config: dict = config
		self.interpreter = interpreter
		self._epsilon: float = self.config["epsilon"]
		self._q_table: dict = {}

	def learn(self, environment: object) -> bool:
		state: str = None
		action: int = 0

		while environment.state is True:
			state = self._get_state(environment)
			action = self._perform_action(environment, state, self._epsilon)
			self._update_q_table(environment, state, action, environment.reward)
			self._epsilon *= (1 - self.config["epsilon_decay"])
			yield False
		yield True

	def play(self, environment: object) -> bool:
		state: str = None
		action: int = 0

		while environment.state is True:
			state = self._get_state(environment)
			action = self._perform_action(environment, state, 0)
			yield False
		yield True

	def load(self, path: str) -> None:
		with open(path, "r") as file:
			self._q_table = json.load(file)

	def save(self, path: str) -> None:
		with open(path, "w") as file:
			file.write(json.dumps(self._q_table, indent=4))

	def _get_state(self, environment: object) -> str:
		state: str = self.interpreter.compute_state(environment)

		if state not in self._q_table:
			self._q_table[state] = [0.0] * environment.action_space
		return state

	def _perform_action(self, environment: object, state: str, epsilon: float) -> int:
		q_values: list[float] = self._q_table[state]
		q_value: float = max(q_values)
		best_actions: list[float] = None
		action: int = 0

		if random.random() < epsilon:
			action = random.randint(0, environment.action_space - 1)
		else:
			best_actions = [index for index, action in enumerate(q_values) if action == q_value]
			action = random.choice(best_actions)
		environment.action(action)
		return action

	def _update_q_table(self, environment: object, state: str, action: int, reward: float) -> None:
		current_q_value: float = self._q_table[state][action]
		updated_q_value: float = current_q_value
		new_state: str = None
		target: float = reward

		# Todo: fix selecting bias
		if environment.state is True:
			new_state = self._get_state(environment)
			target += self.config["gamma"] * max(self._q_table[new_state])
		updated_q_value += self.config["learning_rate"] * (target - current_q_value)
		self._q_table[state][action] = round(updated_q_value, self.config["precision"])
