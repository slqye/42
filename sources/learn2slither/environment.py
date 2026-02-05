import random

class Environment:
	def __init__(self, config: dict) -> None:
		self.board: Board = Board(config["board"])
		self.snake: Snake = Snake(config["snake"])
		self.state: bool = True
		self._snake_start: list[int] = None

		for consumable, number in self.board.config["consumables"].items():
			for _ in range(number):
				self.spawn(self.board.config["encoding"][consumable])
		self._snake_start = self.spawn(self.board.config["encoding"]["snake_head"])
		self.snake.state.append(self._snake_start)

	def __str__(self) -> str:
		display: list[str] = []

		display.append(self.snake.__str__())
		display.append(self.board.__str__())
		return "\n".join(display)

	def spawn(self, spawned: str) -> list[int]:
		cell: list[int, int] = self.board.get_spawnable_cell()

		if cell != None:
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
			self.state = False
		elif cell == self.board.config["encoding"]["snake_body"]:
			self.state = False
		elif cell == self.board.config["encoding"]["apple_green"]:
			self.snake.grow()
			self.board.update(self.snake)
			self.spawn(self.board.config["encoding"]["apple_green"])
		elif cell == self.board.config["encoding"]["apple_red"]:
			self.board.update(self.snake)
			if self.snake.length - 1 == 0:
				self.state = False
			else:
				self.snake.shrink()
				self.board.update(self.snake)
				self.spawn(self.board.config["encoding"]["apple_red"])
		else:
			self.board.update(self.snake)

class Board:
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
		display: list[str] = [str(row) for row in self.state]

		return "\n".join(display)

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

	def __str__(self) -> str:
		display: list[str] = []

		display.append(str(self.state))
		display.append(str(self.length))
		return " ".join(display)

	@property
	def length(self) -> int:
		return len(self.state)

	def move_left(self):
		self.update([self.state[0][0], self.state[0][1] - 1])

	def move_up(self):
		self.update([self.state[0][0] - 1, self.state[0][1]])

	def move_right(self):
		self.update([self.state[0][0], self.state[0][1] + 1])
	
	def move_down(self):
		self.update([self.state[0][0] + 1, self.state[0][1]])

	def grow(self) -> None:
		self.state.append(self.state[-1])
	
	def shrink(self) -> None:
		self.state.pop()

	def update(self, position: list[int]) -> None:
		for index in range(len(self.state) - 1):
			self.state[index + 1] = self.state[index]
		self.state[0] = position
