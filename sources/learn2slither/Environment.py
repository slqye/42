import abc
import random

class IEnvironment(abc.ABC):
	@property
	@abc.abstractmethod
	def action_space(self) -> int:
		pass

	@property
	@abc.abstractmethod
	def reward(self) -> float:
		pass

	@abc.abstractmethod
	def action(self, action: int) -> None:
		pass

class SnakeEnvironment(IEnvironment):
	ACTION_SPACE = 4
	EVENT_NOTHING = 0
	EVENT_DIE = 1
	EVENT_GROW = 2
	EVENT_SHRINK = 3

	def __init__(self, config: dict) -> None:
		self.config: dict = config
		self.board: SnakeBoard = SnakeBoard(self.config["board"])
		self.snake: Snake = Snake(self.config["snake"])
		self.state: bool = True
		self.event: int = self.EVENT_NOTHING
		self._snake_start: list[int] = None

		if config["board"]["size"] < 4:
			raise Exception("board size too small")
		for consumable, number in self.board.config["consumables"].items():
			for _ in range(number):
				self.spawn(self.board.config["encoding"][consumable])
		self._snake_start = self.spawn(self.board.config["encoding"]["snake_head"])
		self.snake.state.append(self._snake_start)
		for _ in range(self.snake.config["length"] - 1):
			self.snake.grow()

	def __str__(self) -> str:
		display: list[str] = []

		display.append(self.board.__str__())
		return "\n".join(display)

	@property
	def action_space(self) -> int:
		return self.ACTION_SPACE

	@property
	def reward(self) -> float:
		match self.event:
			case self.EVENT_NOTHING:
				return self.config["rewards"]["nothing"]
			case self.EVENT_DIE:
				return self.config["rewards"]["die"]
			case self.EVENT_GROW:
				return self.config["rewards"]["grow"]
			case self.EVENT_SHRINK:
				return self.config["rewards"]["shrink"]

	def spawn(self, spawned: str) -> list[int]:
		cell: list[int, int] = self.board.get_spawnable_cell()

		if cell is not None:
			self.board.state[cell[0]][cell[1]] = spawned
		return cell

	def action(self, action: int) -> None:
		actions: dict = {
			0: self.snake.move_left,
			1: self.snake.move_up,
			2: self.snake.move_right,
			3: self.snake.move_down
		}

		actions[action]()
		self._action_hook()

	def _action_hook(self) -> None:
		snake_position: list[int] = self.snake.state[0]
		cell: str = self.board.state[snake_position[0]][snake_position[1]]

		if cell == self.board.config["encoding"]["wall"]:
			self.event = self.EVENT_DIE
			self.state = False
		elif cell == self.board.config["encoding"]["snake_body"]:
			self.event = self.EVENT_DIE
			self.state = False
		elif cell == self.board.config["encoding"]["apple_green"]:
			self.event = self.EVENT_GROW
			self.snake.grow()
			self.board.update(self.snake)
			self.spawn(self.board.config["encoding"]["apple_green"])
		elif cell == self.board.config["encoding"]["apple_red"]:
			self.board.update(self.snake)
			if self.snake.length - 1 == 0:
				self.event = self.EVENT_DIE
				self.state = False
			else:
				self.event = self.EVENT_SHRINK
				self.snake.shrink()
				self.board.update(self.snake)
				self.spawn(self.board.config["encoding"]["apple_red"])
		else:
			self.event = self.EVENT_NOTHING
			self.board.update(self.snake)

class SnakeBoard:
	def __init__(self, config: dict) -> None:
		self.config: dict = config
		self.state: list[list[str]] = []

		for row in range(self.config["size"]):
			self.state.append([])
			for column in range(self.config["size"]):
				if row == 0 or row == self.config["size"] - 1:
					self.state[row].append(self.config["encoding"]["wall"])
					continue
				if column == 0 or column == self.config["size"] - 1:
					self.state[row].append(self.config["encoding"]["wall"])
					continue
				self.state[row].append(self.config["encoding"]["empty"])

	def __str__(self) -> str:
		display: list[str] = [row for row in self.state]

		return "\n".join(["".join(row) for row in display])

	def update(self, snake: object) -> None:
		for row in range(self.config["size"]):
			for column in range(self.config["size"]):
				if self.state[row][column] == self.config["encoding"]["snake_head"]:
					self.state[row][column] = self.config["encoding"]["empty"]
				if self.state[row][column] == self.config["encoding"]["snake_body"]:
					self.state[row][column] = self.config["encoding"]["empty"]
		for index, position in enumerate(snake.state):
			if index == 0:
				self.state[position[0]][position[1]] = self.config["encoding"]["snake_head"]
			else:
				self.state[position[0]][position[1]] = self.config["encoding"]["snake_body"]

	def get_spawnable_cell(self) -> list[int]:
		cells: list[tuple[int]] = []

		for row in range(self.config["size"]):
			for column in range(self.config["size"]):
				if self.state[row][column] == self.config["encoding"]["empty"]:
					cells.append((row, column))
		return None if len(cells) == 0 else random.choice(cells)

class Snake:
	def __init__(self, config: dict):
		self.config: dict = config
		self.state: list[tuple[int, int]] = []
		self.moves: int = 0

	def __str__(self) -> str:
		display: list[str] = []

		display.append(str(self.state))
		display.append(str(self.length))
		return " ".join(display)

	@property
	def position(self) -> list[int]:
		return self.state[0]

	@property
	def length(self) -> int:
		return len(self.state)

	def move_left(self):
		self.moves += 1
		self.update([self.state[0][0], self.state[0][1] - 1])

	def move_up(self):
		self.moves += 1
		self.update([self.state[0][0] - 1, self.state[0][1]])

	def move_right(self):
		self.moves += 1
		self.update([self.state[0][0], self.state[0][1] + 1])

	def move_down(self):
		self.moves += 1
		self.update([self.state[0][0] + 1, self.state[0][1]])

	def grow(self) -> None:
		self.state.append(self.state[-1])

	def shrink(self) -> None:
		self.state.pop()

	def update(self, position: list[int]) -> None:
		for index in range(len(self.state) - 1, 0, -1):
			self.state[index] = self.state[index - 1]
		self.state[0] = position
