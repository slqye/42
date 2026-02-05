import abc
import random
import logging

class Agent(abc.ABC):
	pass

class SnakeAgent(Agent):
	GREED			= 1.0
	LEARNING_RATE	= 0.1
	GAMMA			= 0.9

	ACTION_COUNT			= 4

	ACTION_GAME_OVER		= -10
	ACTION_NOTHING			= -0.1
	ACTION_EAT_GREEN_APPLE	= 10
	ACTION_EAT_RED_APPLE	= -2

	def __init__(self, interpreter: object) -> None:
		self._q_table: dict = {}
		self._interpreter: object = interpreter
		self._greed: float = self.GREED
		self._state: str = None
		self._length: int = None
		self._action: int = None
		self._reward: float = None

	def get_state(self) -> None:
		state: str = self._interpreter.compute_state()

		if state not in self._q_table.keys():
			self._q_table[state] = [0.0] * self.ACTION_COUNT
		return state

	def perform_action(self, environment: object) -> None:
		self._state = self.get_state()
		self._length = environment.get_snake_length()

		if random.random() < self._greed and self._greed > 0:
			self._action = random.randint(0, self.ACTION_COUNT - 1)
		else:
			q_values = self._q_table[self._state]
			max_q = max(q_values)
			best_actions = [i for i, q in enumerate(q_values) if q == max_q]
			self._action = random.choice(best_actions)

		environment.action(self._action)

	def mesure_reward(self, environment) -> None:
		if environment.running is False:
			self._reward = self.ACTION_GAME_OVER
		elif environment.get_snake_length() > self._length:
			self._reward = self.ACTION_EAT_GREEN_APPLE
		elif environment.get_snake_length() < self._length:
			self._reward = self.ACTION_EAT_RED_APPLE
		else:
			self._reward = self.ACTION_NOTHING

	def update_q_table(self, environment) -> None:
		current_q_value: float = self._q_table[self._state][self._action]
		updated_q_value: float = current_q_value
		new_state: str = None

		if environment.running:
			new_state = self.get_state()
			target = self._reward + self.GAMMA * max(self._q_table[new_state])
		else:
			target = self._reward
		updated_q_value += self.LEARNING_RATE * (target - current_q_value)
		self._q_table[self._state][self._action] = round(updated_q_value, 5)
