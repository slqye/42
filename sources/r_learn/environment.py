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

	ACTION_LEFT		= 0
	ACTION_RIGHT	= 1
	ACTION_UP		= 2
	ACTION_DOWN		= 3

	def __init__(self, size: int) -> None:
		assert size >= 2, "size can't be less than 2."

		self.board: list[list[str]] = [
			[
				self.EMPTY
				if x_index != 0 and x_index != size + 1
				else self.WALL
				for x_index in range(size + 2)
			]
			if y_index != 0 and y_index != size + 1
			else [self.WALL] * (size + 2)
			for y_index in range(size + 2)
		]
		self.running = True
		self._size: int = size + 2
		self._snake: list = []

		self._snake.append(self.spawn(self.SNAKE_HEAD))
		for _ in range(self.GREEN_APPLE_COUNT):
			self.spawn(self.GREEN_APPLE)
		for _ in range(self.RED_APPLE_COUNT):
			self.spawn(self.RED_APPLE)

	def __str__(self) -> None:
		display: list[str] = [str(row) for row in self.board]

		return "\n".join(display)

	def spawn(self, spawned: str) -> list[int, int]:
		cells: list[tuple[int, int]] = self._get_board_empty_cells()
		position: list[int, int] = random.choice(cells)

		self.board[position[0]][position[1]] = spawned
		return position

	def action(self, action: int) -> None:
		moves: dict = {
			self.ACTION_LEFT: self._move_left,
			self.ACTION_RIGHT: self._move_right,
			self.ACTION_UP: self._move_up,
			self.ACTION_DOWN: self._move_down
		}

		if self.running is False:
			return
		self.board[self._snake[-1][0]][self._snake[-1][1]] = self.EMPTY
		self._action_hook(moves[action])
		if self.running:
			self._update_snake()

	def _action_hook(self, action: callable) -> None:
		action()
		match self.board[self._snake[0][0]][self._snake[0][1]]:
			case self.WALL:
				self.running = False
			case self.SNAKE_BODY:
				self.running = False
			case self.GREEN_APPLE:
				self._snake.append(self._snake[-1])
			case self.RED_APPLE:
				self._snake.pop()
				if len(self._snake) == 0:
					self.running = False

	def _update_snake(self) -> None:
		self.board[self._snake[-1][0]][self._snake[-1][1]] = self.EMPTY
		for index, snake in enumerate(reversed(self._snake)):
			if index != len(self._snake) - 1:
				self._snake[index] = self._snake[index - 1]
		for index, snake in enumerate(self._snake):
			if index != 0:
				self.board[snake[0]][snake[1]] = self.SNAKE_BODY
		self.board[self._snake[0][0]][self._snake[0][1]] = self.SNAKE_HEAD

	def _move_left(self) -> None:
		self._snake[0] = [self._snake[0][0], self._snake[0][1] - 1]

	def _move_right(self) -> None:
		self._snake[0] = [self._snake[0][0], self._snake[0][1] + 1]

	def _move_up(self) -> None:
		self._snake[0] = [self._snake[0][0] - 1, self._snake[0][1]]

	def _move_down(self) -> None:
		self._snake[0] = [self._snake[0][0] + 1, self._snake[0][1]]

	def _get_board_empty_cells(self) -> dict:
		cells: list[tuple[int, int]] = []

		for row in range(self._size):
			for column in range(self._size):
				if self.board[row][column] == self.EMPTY:
					cells.append((row, column))
		return cells
