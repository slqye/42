import collections
import copy
import itertools
import math

class Table:
	"""
	Main class that compute pruning tables.
	"""
	MOVES_G0 = ("U", "U'", "U2", "D", "D'", "D2", "F", "F'", "F2", "B", "B'", "B2", "R", "R'", "R2", "L", "L'", "L2")
	MOVES_G1 = ("U2", "D2", "F", "F'", "F2", "B", "B'", "B2", "R", "R'", "R2", "L", "L'", "L2")
	MOVES_G2 = ("U2", "D2", "F2","B2", "R", "R'", "R2", "L", "L'", "L2")
	MOVES_G3 = ("U2", "D2", "F2", "B2", "R2", "L2")
	MSE_SLICES = {"M": (0, 9, 11, 3), "S": (2, 8, 10, 1), "E": (7, 4, 5, 6)}

	def __init__(self, cube: object) -> None:
		"""
		Default init function.
		"""
		self._cube: object = cube

	def compute(self, phase: callable, moves: tuple, output: str) -> None:
		"""
		Compute the phase's lookup table.
		"""
		table: dict = self._bfs(self._cube, phase, moves)
		position: int = 0
		depth: int = 0
		moves: str = ""

		with open(output, "w") as file:
			for key in table.keys():
				position = key
				depth = table[key][0]
				moves = "".join(table[key][1][::-1])
				file.write(f"{position} {depth} {moves if len(moves) != 0 else 'E'}\n")

	@staticmethod
	def phase_1(cube: object) -> int:
		"""
		Compute phase 1 (g0->g1) cube state.
		"""
		return sum(cube._edge_orientations[index] << index for index in range(12))

	@staticmethod
	def phase_2(cube: object) -> int:
		"""
		Compute phase 2 (g1->g2) cube state.
		"""
		corners_encoding: int = 0
		edges_encoding: int = 0
		edges: list = (0, 3, 9, 11)

		for index, i in enumerate(cube._corner_orientations):
			corners_encoding *= 3
			corners_encoding += i
		for index, i in enumerate(cube._edge_positions):
			if i in edges:
				edges_encoding |= (1 << index)
		return corners_encoding * 6561 + edges_encoding

	@staticmethod
	def phase_3(cube: object) -> int:
		"""
		Compute phase 3 (g2->g3) cube state.
		"""
		length: int = len(cube._corner_positions)
		edge_configuration: list = [x for x in cube._edge_positions if x not in Table.MSE_SLICES["M"]]
		corner_encoding: int = 0
		edges_encoding: int = 0

		for i in range(length):
			corner_encoding *= (length - i)
			for j in range(i + 1, length):
				if cube._corner_positions[i] > cube._corner_positions[j]:
					corner_encoding += 1
		for index, edge in enumerate(edge_configuration):
			if edge in Table.MSE_SLICES["S"]:
				edges_encoding |= (1 << index)
		edges_encoding = Table._rank_4_8(edges_encoding)
		return corner_encoding * 70 + edges_encoding

	@staticmethod
	def phase_4(cube: object) -> int:
		"""
		Compute phase 4 (g3->g4) cube state.
		"""
		corner_rank = 0
		corners = list(cube._corner_positions)
		for i in range(7):
			count = 0
			for j in range(i + 1, 8):
				if corners[i] > corners[j]:
					count += 1
			corner_rank = corner_rank * (8 - i) + count
		edge_rank = 0
		edges = list(cube._edge_positions)
		for i in range(11):
			count = 0
			for j in range(i + 1, 12):
				if edges[i] > edges[j]:
					count += 1
			edge_rank = edge_rank * (12 - i) + count
		return corner_rank * 39916800 + edge_rank

	@staticmethod
	def _bfs(cube: object, phase: callable, moves: list) -> dict:
		"""
		Generic BFS algorithm.
		"""
		queue: object = collections.deque()
		result: dict = {}
		depth: int = 0
		position: int = 0

		queue.append((cube, []))
		result[0] = (position, [])
		while queue:
			size = len(queue)
			depth += 1
			print(f"\r[{phase.__name__}]: {depth} {len(result.keys())}", end="", flush=True)
			for _ in range(size):
				current_cube = queue.popleft()
				for move in moves:
					clone = copy.deepcopy(current_cube[0])
					clone.spin(move)
					position = phase(clone)
					if position not in result.keys():
						result[position] = (depth, current_cube[1] + [cube.SPINS_REVERSE[cube.SPINS.index(move)]])
						queue.append((clone, current_cube[1] + [cube.SPINS_REVERSE[cube.SPINS.index(move)]]))
		print()
		return result

	@staticmethod
	def _rank_4_8(mask: int) -> int:
		rank: int = 0
		k: int = 4

		for i in range(8):
			if mask & (1 << i):
				k -= 1
			else:
				if k > 0:
					rank += math.comb(7 - i, k - 1)
		return rank
