from .cube import Cube

import random

def default(min: int, max: int) -> list:
	"""
	Generate random shuffling state using a minimum and maximum.
	"""
	return random.choices(Cube.SPINS, k=random.randint(min, max))
