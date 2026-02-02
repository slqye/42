import random
import dataclasses

class Snake:
	EMPTY = 0
	PLAYER = 1
	GREEN_APPLE = 2
	RED_APPLE = 3

	@dataclasses.dataclass
	class Configuration:
		board_size: tuple[int, int]
		green_apple_count: int
		red_apple_count: int
		agent: object

	def __init__(self, configuration: object) -> None:
		assert configuration.board_size[0] > 0
		assert configuration.board_size[1] > 0
		assert configuration.green_apple_count > 0
		assert configuration.red_apple_count > 0

		self._board_size: tuple[int, int] = configuration.board_size
		self._board: list[list[int]] = [[self.EMPTY] * self._board_size[0]] * self._board_size[1]
		self._green_apple_count: int = configuration.green_apple_count
		self._red_apple_count: int = configuration.red_apple_count
