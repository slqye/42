from .cube import Cube

import collections
import copy
import itertools
import math

MOVES_G0 = ("U", "U'", "U2", "D", "D'", "D2", "F", "F'", "F2", "B", "B'", "B2", "R", "R'", "R2", "L", "L'", "L2")
MOVES_G1 = ("U2", "D2", "F", "F'", "F2", "B", "B'", "B2", "R", "R'", "R2", "L", "L'", "L2")
MOVES_G2 = ("U2", "D2", "F2","B2", "R", "R'", "R2", "L", "L'", "L2")
MOVES_G3 = ("U2", "D2", "F2", "B2", "R2", "L2")
MSE_SLICES = {"M": (0, 9, 11, 3), "S": (2, 8, 10, 1), "E": (7, 4, 5, 6)}

class Table:
	"""
	Main class that compute pruning tables.
	"""

	def __init__(self, phase: callable, moves: tuple, debug: bool = False) -> None:
		"""
		Default init function.
		"""
		self._phase: callable = phase
		self._cube: object = Cube()
		self._table: dict = {}
		self._moves = moves
		self._debug = debug

	def compute(self) -> None:
		"""
		Generic BFS algorithm.
		"""
		queue: object = collections.deque()
		result: dict = {}
		depth: int = 0
		position: int = 0

		queue.append((self._cube, []))
		result[0] = (position, [])
		while queue:
			size = len(queue)
			depth += 1
			if self._debug:
				print(f"\r{self._phase.__name__}: {depth} {len(result.keys())}", end="", flush=True)
			for _ in range(size):
				current_cube = queue.popleft()
				for move in self._moves:
					clone = copy.deepcopy(current_cube[0])
					clone.spin(move)
					position = self._phase(clone)
					if position not in result.keys():
						result[position] = (depth, current_cube[1] + [self._cube.SPINS_REVERSE[self._cube.SPINS.index(move)]])
						queue.append((clone, current_cube[1] + [self._cube.SPINS_REVERSE[self._cube.SPINS.index(move)]]))
		print() if self._debug else None
		self._table = result

	def save(self, output: str) -> None:
		"""
		Save table to a file.
		"""
		position: int = 0
		depth: int = 0
		moves: str = ""

		with open(output, "w") as file:
			for key in self._table.keys():
				position = key
				depth = self._table[key][0]
				moves = "".join(self._table[key][1][::-1])
				file.write(f"{position} {depth} {moves if len(moves) != 0 else 'E'}\n")

def phase_1(cube: object) -> int:
	"""
	Compute phase 1 (g0->g1) cube state.
	"""
	return sum(cube._edge_orientations[index] << index for index in range(12))

def phase_2(cube: object) -> int:
	"""
	Compute phase 2 (g1->g2) cube state.
	"""
	corners_encoding: int = 0
	edge_encodings: int = 0

	for index, corner in enumerate(cube._corner_orientations):
		corners_encoding = corners_encoding * 3 + corner
	for index, edge in enumerate(cube._edge_positions):
		if edge in MSE_SLICES["M"]:
			edge_encodings |= (1 << index)
	return corners_encoding * 2 ** 12 + edge_encodings

def phase_3(cube: object) -> int:
	"""
	Compute phase 3 (g2->g3) cube state.
	"""
	edge_configuration: list = [x for x in cube._edge_positions if x not in MSE_SLICES["M"]]
	corner_lengths: int = len(cube._corner_positions)
	corner_encodings: int = 0
	edge_encodings: int = 0
	combinations: list = list(itertools.combinations(range(8), 4))

	for index in range(corner_lengths):
		corner_encodings *= (corner_lengths - index)
		for j in range(index + 1, corner_lengths):
			if cube._corner_positions[index] > cube._corner_positions[j]:
				corner_encodings += 1
	for index, edge in enumerate(edge_configuration):
		if edge in MSE_SLICES["S"]:
			edge_encodings |= (1 << index)
	edge_encodings = combinations.index(tuple(i for i in range(8) if edge_encodings & (1 << i)))
	return corner_encodings * 70 + edge_encodings

def phase_4(cube: object) -> int:
	"""
	Compute phase 4 (g3->g4) cube state.
	"""
	corner_lengths: int = len(cube._corner_positions)
	edge_lengths: int = len(cube._edge_positions)
	corner_encodings: int = 0
	edge_encodings: int = 0

	for index in range(corner_lengths - 1):
		corner_encodings *= (corner_lengths - index)
		for j in range(index + 1, corner_lengths):
			if cube._corner_positions[index] > cube._corner_positions[j]:
				corner_encodings += 1
	for index in range(edge_lengths - 1):
		edge_encodings *= (edge_lengths - index)
		for j in range(index + 1, edge_lengths):
			if cube._edge_positions[index] > cube._edge_positions[j]:
				edge_encodings += 1
	return corner_encodings * 39916800 + edge_encodings
