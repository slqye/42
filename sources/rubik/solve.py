from .table import Table, phase_0, phase_1, phase_2, phase_3

def thistlethwaite(cube: object) -> list:
	"""
	Solve the cube using Thistlethwaite 4 phases algorithm.
	"""
	phases: list = [phase_0, phase_1, phase_2, phase_3]
	states: list = []
	sequences: list = []

	for index, phase in enumerate(phases):
		states.append(phase(cube))
		sequences.append(_find_cube_state_sequence(index, states[-1]))
		for move in sequences[-1]:
			cube.spin(move)
	return [move for sublist in sequences for move in sublist]

def _find_cube_state_sequence(phase: int, state: int) -> list:
	"""
	Return move sequence corresponding to phase and state of a cube. 
	"""
	result: list = []
	data: list = []

	with open(f"includes/table_{phase}.rubik") as file:
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
