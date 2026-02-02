import abc

class Interpreter(abc.ABC):
	@abc.abstractmethod
	def compute_state(self):
		pass
	

class SnakeInterpreter(Interpreter):
	def __init__(self, environment: object) -> None:
		self.environment = environment

		self.compute_state()

	def compute_state(self) -> tuple[str, str, str, str]:
		snake_position: tuple[int, int] = self._get_snake_position()

		print(snake_position)
		print(self.environment.board[snake_position[0]][snake_position[1] + 1:])
		print(self.environment.board[snake_position[0]][:snake_position[1]])
		print([x[snake_position[1]] for x in self.environment.board])

	def _get_snake_position(self) -> tuple[int, int]:
		for row in range(self.environment._size):
			for column in range(self.environment._size):
				if self.environment.board[row][column] == self.environment.SNAKE_HEAD:
					return (row, column)
