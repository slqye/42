import random

class Shuffle:
	@staticmethod
	def random(moves: list[str]) -> str:
		return ' '.join(random.choices(moves, k=random.randint(10, 50)))

	@staticmethod
	def custom(moves: list[str], length: int) -> str:
		return ' '.join(random.choices(moves, k=length))