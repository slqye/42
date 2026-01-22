class Cube:
	"""
	Main class that represent a rubik's cube and perform operations.
	"""
	SPINS = ["U", "U'", "U2", "D", "D'", "D2", "F", "F'", "F2", "B", "B'", "B2", "R", "R'", "R2", "L", "L'", "L2"]
	SPINS_REVERSE = ["U'", "U", "U2", "D'", "D", "D2", "F'", "F", "F2", "B'", "B", "B2", "R'", "R", "R2", "L'", "L", "L2"]
	SPINS_EDGES = {
		"U": ((0, 1, 2, 3, 4, 5, 6, 7, 9, 10, 11, 8), (8, 9, 10, 11)),
		"U'": ((0, 1, 2, 3, 4, 5, 6, 7, 11, 8, 9, 10), (8, 9, 10, 11)),
		"U2": ((0, 1, 2, 3, 4, 5, 6, 7, 10, 11, 8, 9), ()),
		"D": ((2, 0, 3, 1, 4, 5, 6, 7, 8, 9, 10, 11), (0, 1, 2, 3)),
		"D'": ((1, 3, 0, 2, 4, 5, 6, 7, 8, 9, 10, 11), (0, 1, 2, 3)),
		"D2": ((3, 2, 1, 0, 4, 5, 6, 7, 8, 9, 10, 11), ()),
		"F": ((5, 1, 2, 3, 0, 9, 6, 7, 8, 4, 10, 11), ()),
		"F'": ((4, 1, 2, 3, 9, 0, 6, 7, 8, 5, 10, 11), ()),
		"F2": ((9, 1, 2, 3, 5, 4, 6, 7, 8, 0, 10, 11), ()),
		"B": ((0, 1, 2, 7, 4, 5, 3, 11, 8, 9, 10, 6), ()),
		"B'": ((0, 1, 2, 6, 4, 5, 11, 3, 8, 9, 10, 7), ()),
		"B2": ((0, 1, 2, 11, 4, 5, 7, 6, 8, 9, 10, 3), ()),
		"R": ((0, 6, 2, 3, 4, 1, 10, 7, 8, 9, 5, 11), ()),
		"R'": ((0, 5, 2, 3, 4, 10, 1, 7, 8, 9, 6, 11), ()),
		"R2": ((0, 10, 2, 3, 4, 6, 5, 7, 8, 9, 1, 11), ()),
		"L": ((0, 1, 4, 3, 8, 5, 6, 2, 7, 9, 10, 11), ()),
		"L'": ((0, 1, 7, 3, 2, 5, 6, 8, 4, 9, 10, 11), ()),
		"L2": ((0, 1, 8, 3, 7, 5, 6, 4, 2, 9, 10, 11), ())
	}
	SPINS_CORNERS = {
		"U": ((1, 5, 2, 3, 0, 4, 6, 7), (-1, 1, 0, 0, 1, -1, 0, 0)),
		"U'": ((4, 0, 2, 3, 5, 1, 6, 7), (-1, 1, 0, 0, 1, -1, 0, 0)),
		"U2": ((5, 4, 2, 3, 1, 0, 6, 7), ()),
		"D": ((0, 1, 3, 7, 4, 5, 2, 6), (0, 0, -1, 1, 0, 0, 1, -1)),
		"D'": ((0, 1, 6, 2, 4, 5, 7, 3), (0, 0, -1, 1, 0, 0, 1, -1)),
		"D2": ((0, 1, 7, 6, 4, 5, 3, 2), ()),
		"F": ((3, 0, 1, 2 , 4, 5, 6, 7), (1, -1 , 1, -1, 0, 0, 0, 0)),
		"F'": ((1, 2, 3, 0, 4, 5, 6, 7), (1, -1, 1, -1, 0, 0, 0, 0)),
		"F2": ((2, 3, 0, 1, 4, 5, 6, 7), ()),
		"B": ((0, 1, 2, 3, 5, 6, 7, 4), (0, 0, 0, 0, -1, 1, -1, 1)),
		"B'": ((0, 1, 2, 3, 7, 4, 5, 6), (0, 0, 0, 0, -1, 1, -1, 1)),
		"B2": ((0, 1, 2, 3, 6, 7, 4, 5), ()),
		"R": ((0, 2, 6, 3, 4, 1, 5, 7), ()),
		"R'": ((0, 5, 1, 3, 4, 6, 2, 7), ()),
		"R2": ((0, 6, 5, 3, 4, 2, 1, 7), ()),
		"L": ((4, 1, 2, 0, 7, 5, 6, 3), ()),
		"L'": ((3, 1, 2, 7, 0, 5, 6, 4), ()),
		"L2": ((7, 1, 2, 4, 3, 5, 6, 0), ())
	}

	def __init__(self) -> None:
		"""
		Default init function.
		"""
		self._edge_positions = list(range(12))
		self._edge_orientations = [0] * 12
		self._corner_positions = list(range(8))
		self._corner_orientations = [0] * 8
		self._debug = False

	def __str__(self) -> str:
		"""
		Default str function.
		"""
		display: list[str] = []

		display.append(f"edge_positions:\t\t{self._edge_positions}")
		display.append(f"edge_orientations:\t{self._edge_orientations}")
		display.append(f"corner_positions:\t{self._corner_positions}")
		display.append(f"corner_orientations:\t{self._corner_orientations}")
		return "\n".join(display)

	def spin(self, move: str) -> None:
		"""
		Apply a move on the cube.
		"""
		edge_positions_holder: list = [0] * 12
		edge_orientations_holder: list = [0] * 12
		corner_positions_holder: list = [0] * 8
		corner_orientations_holder: list = [0] * 8

		if move not in self.SPINS:
			raise ValueError(f"Invalid move: \"{move}\"")
		for index in range(12):
			edge_positions_holder[index] = self._edge_positions[self.SPINS_EDGES[move][0][index]]
			edge_orientations_holder[index] = self._edge_orientations[self.SPINS_EDGES[move][0][index]]
		for index in self.SPINS_EDGES[move][1]:
			edge_orientations_holder[index] ^= 1
		for index in range(8):
			corner_positions_holder[index] = self._corner_positions[self.SPINS_CORNERS[move][0][index]]
			corner_orientations_holder[index] = self._corner_orientations[self.SPINS_CORNERS[move][0][index]]
			if self.SPINS_CORNERS[move][1] != ():
				corner_orientations_holder[index] += self.SPINS_CORNERS[move][1][index]
				corner_orientations_holder[index] %= 3
		self._edge_positions = edge_positions_holder
		self._edge_orientations = edge_orientations_holder
		self._corner_positions = corner_positions_holder
		self._corner_orientations = corner_orientations_holder
