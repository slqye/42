from .table import Table
from .cube import Cube
from .shuffle import Shuffle

class Solve:
	@staticmethod
	def regroup_moves(moves: str) -> str:
		"""
		Regroup moves by removing spaces.
		Example: "U2 D L2" -> "U2DL2"
		"""
		return moves.replace(" ", "")

	@staticmethod
	def space_moves(moves: str) -> str:
		"""
		Add spaces between moves.
		Example: "U2DL2" -> "U2 D L2"
		"""
		result = []
		i = 0
		while i < len(moves):
			move = moves[i:i+2]
			if move in Cube.SPINS:
				result.append(move)
				i += 2
			else:
				result.append(moves[i])
				i += 1
		return " ".join(result)

	@staticmethod
	def thistlethwaite(cube: object) -> str:
		"""
		Solve the cube.
		"""
		phases: list = [Table.phase_1]#, Table.phase_2. Table.phase_3, Table.phase_4]
		states: list = []
		sequences: list = []

		def find_sequence(phase: int, index: int) -> str:
			with open(f"includes/phase_{phase}.table") as file:
				for line in file:
					if int(line.split()[0]) == index:
						return line.split()[2] if line.split()[2] != "E" else ""
		for index, phase in enumerate(phases):
			states.append(phase(cube))
			sequences.append(find_sequence(index, states[-1]))
			for move in sequences[-1]:
				print(move)
				cube.spin(move)
		return (Solve.space_moves("".join(sequences)))

	@staticmethod
	def miracle(cube: object) -> str:
		"""
		Solve the cube using the miracle method.
		"""
		return ("")

	@staticmethod
	def bogo(cube: object) -> str:
		"""
		Solve the cube using the bogo method.
		"""
		return
		initial_edge_positions = cube._edge_positions.copy()
		initial_edge_orientations = cube._edge_orientations.copy()
		initial_corner_positions = cube._corner_positions.copy()
		initial_corner_orientations = cube._corner_orientations.copy()
		while True:
			random_moves = Shuffle.random(Cube.SPINS)
			cube._edge_positions = initial_edge_positions.copy()
			cube._edge_orientations = initial_edge_orientations.copy()
			cube._corner_positions = initial_corner_positions.copy()
			cube._corner_orientations = initial_corner_orientations.copy()
			cube.spin_sequence(Solve.regroup_moves(random_moves))
			if (cube._edge_positions == list(range(12)) and
				cube._edge_orientations == [0] * 12 and
				cube._corner_positions == list(range(8)) and
				cube._corner_orientations == [0] * 8):
				return random_moves
			print(f"Trying sequence: {random_moves}") if cube._debug else None
		return ("")
