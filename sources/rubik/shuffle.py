import random

class Shuffle:
	"""
	Main class for generating the shuffling state.
	"""
	MIN = 10
	MAX = 25

	@staticmethod
	def random(moves: list) -> list:
		"""
		Generate random shuffling state using MIN and MAX.
		"""
		return random.choices(moves, k=random.randint(Shuffle.MIN, Shuffle.MAX))

	@staticmethod
	def custom(moves: list, length: int) -> list:
		"""
		Generate random shuffling state using custom input.
		"""
		return random.choices(moves, k=length)
