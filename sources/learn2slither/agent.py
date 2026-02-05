import random

class Agent:
	ACTION_COUNT = 4

	def __init__(self, config: dict, interpreter: object) -> None:
		self.config: dict = config
		self._interpreter = interpreter
		self._q_table: dict = {}

	def learn(self, environment: object) -> bool:
		state: str = None
		greed: float = self.config["epsilon"]
		action: int = 0
		reward: int = 0

		while environment.state is True:
			state = self._get_state(environment)
			action = self._perform_action(environment, state, greed)
			reward = self._get_reward(environment)
			self._update_q_table(environment, state, action, reward)
			greed -= self.config["epsilon_decay"]
			yield False
		yield True

	def _get_state(self, environment: object) -> str:
		state: str = self._interpreter.compute_state(environment)

		if state not in self._q_table:
			self._q_table[state] = [0.0] * self.ACTION_COUNT
		return state

	def _perform_action(self, environment: object, state: str, greed: float) -> int:
		q_values: list[float] = self._q_table[state]
		q_value: float = max(q_values)
		best_actions: list[float] = None
		action: int = 0

		if random.random() < greed:
			q_value = random.randint(0, self.ACTION_COUNT - 1)
		else:
			best_actions = [index for index, action in enumerate(q_values) if action == q_value]
			action = random.choice(best_actions)
		environment.action(action)
		return action

	def _get_reward(self, environment: object) -> None:
		rewards: dict = {
			environment.EVENT_NOTHING: self.config["rewards"]["nothing"],
			environment.EVENT_DIE: self.config["rewards"]["die"],
			environment.EVENT_GROW: self.config["rewards"]["grow"],
			environment.EVENT_SHRINK: self.config["rewards"]["shrink"],
		}

		return rewards[environment.event]

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
