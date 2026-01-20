from .table import Table
from .cube import Cube
from .shuffle import Shuffle

class Solve:
	"""
	Main class that solve a cube.
	"""

	@staticmethod
	def thistlethwaite(cube: object) -> list:
		"""
		Solve the cube using Thistlethwaite 4 phases algorithm.
		"""
		phases: list = [Table.phase_1, Table.phase_2, Table.phase_3, Table.phase_4]
		states: list = []
		sequences: list = []

		for index, phase in enumerate(phases):
			states.append(phase(cube))
			sequences.append(Solve._find_cube_state_sequence(index + 1, states[-1]))
			for move in sequences[-1]:
				cube.spin(move)
		return [move for sublist in sequences for move in sublist]

	@staticmethod
	def _find_cube_state_sequence(phase: int, state: int) -> list:
		"""
		Return move sequence corresponding to phase and state of a cube. 
		"""
		result: list = []
		data: list = []

		with open(f"includes/phase_{phase}.table") as file:
			for line in file:
				if int(line.split()[0]) == state:
					data = line.split()
					if data[2] == "E":
						return result
					data = "".join(data[2])
					for char in data:
						if char in "'2":
							result[-1] += char
						else:
							result.append(char)
					return result
