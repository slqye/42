import abc
import random

class Environment(abc.ABC):
	pass

class SnakeEnvironment(Environment):
	EMPTY		= "0"
	WALL		= "W"
	SNAKE_HEAD	= "H"
	SNAKE_BODY	= "S"
	GREEN_APPLE	= "G"
	RED_APPLE	= "R"

	GREEN_APPLE_COUNT	= 2
	RED_APPLE_COUNT		= 1

	def __init__(self, size: int) -> None:
		assert size >= 10, "size can't be less than 10"

		self._size: int = size
		self.board: list[list[str]] = [
			[self.EMPTY for _ in range(self._size)]
			for _ in range(self._size)
		]

		self.spawn(self.SNAKE_HEAD)
		for _ in range(self.GREEN_APPLE_COUNT):
			self.spawn(self.GREEN_APPLE)
		for _ in range(self.GREEN_APPLE_COUNT):
			self.spawn(self.RED_APPLE)

	def __str__(self) -> None:
		display: list[str] = ["".join(row) for row in self.board]

		return "\n".join(display)

	def spawn(self, spawned: str) -> None:
		cells: list[tuple[int, int]] = self._get_board_empty_cells()
		position: tuple[int, int] = random.choice(cells)

		self.board[position[0]][position[1]] = spawned

	def _get_board_empty_cells(self) -> dict:
		cells: list[tuple[int, int]] = []

		for row in range(self._size):
			for column in range(self._size):
				if self.board[row][column] == self.EMPTY:
					cells.append((row, column))
		return cells
