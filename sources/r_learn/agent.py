import abc
import random

class Agent(abc.ABC):
	pass

class SnakeAgent(Agent):
	GREED			= 0.25
	LEARNING_RATE	= 0.80
	GAMMA			= 0.95

	ACTION_COUNT			= 4
	ACTION_GAME_OVER		= -10
	ACTION_NOTHING			= -0.1
	ACTION_EAT_GREEN_APPLE	= 1
	ACTION_EAT_RED_APPLE	= -1

	def __init__(self, interpreter: object) -> None:
		self._q_table: dict = {}
		self._interpreter: object = interpreter
		self._state: str = None
		self._previous_length: int = None
		self._action: int = None
		self._reward: float = None

	def perform_action(self, environment: object) -> None:
		self._state = self._interpreter.compute_state()
		self._previous_length = environment.get_snake_length()
		if self._state not in self._q_table:
			self._q_table[self._state] = [0] * self.ACTION_COUNT
		if random.random() > self.GREED:
			self._action = random.randint(0, self.ACTION_COUNT - 1)
		else:
			self._action = self._q_table[self._state].index(max(self._q_table[self._state]))
		environment.action(self._action)

	def mesure_reward(self, environment) -> None:
		if environment.running is False:
			self._reward = self.ACTION_GAME_OVER
		elif environment.get_snake_length() > self._previous_length:
			self._reward = self.ACTION_EAT_GREEN_APPLE
		elif environment.get_snake_length() < self._previous_length:
			self._reward = self.ACTION_EAT_RED_APPLE
		else:
			self._reward = self.ACTION_NOTHING

	def update_q_table(self, environment) -> None:
		current_q_value: float = self._q_table[self._state][self._action]
		updated_q_value: float = current_q_value
		new_state: str = None

		if environment.running:
			new_state = self._interpreter.compute_state()
			if new_state not in self._q_table:
				self._q_table[new_state] = [0] * self.ACTION_COUNT
				updated_q_value += self.LEARNING_RATE * (self._reward + self.GAMMA * max(self._q_table[new_state]) - current_q_value)
		else:
			updated_q_value += self.LEARNING_RATE * (self._reward + self.GAMMA * self.ACTION_GAME_OVER - current_q_value)
		self._q_table[self._state][self._action] = round(updated_q_value, 2)
