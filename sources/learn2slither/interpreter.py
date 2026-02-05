import abc

class Interpreter(abc.ABC):
	@abc.abstractmethod
	def compute_state(self):
		pass

class SnakeInterpreter(Interpreter):
	def __init__(self, environment: object) -> None:
		self.environment = environment

	def compute_state(self) -> str:
		snake_position: tuple[int, int] = self._get_snake_position()
		x_axis: tuple = self.environment.board[snake_position[0]]
		y_axis: tuple = tuple([x[snake_position[1]] for x in self.environment.board])
		result: list  = []

		result.append(x_axis[snake_position[1] - 1])
		result.append(x_axis[snake_position[1] + 1])
		result.append(y_axis[snake_position[0] - 1])
		result.append(y_axis[snake_position[0] + 1])
		result.append(str(self.environment._snake_direction))
		return "".join(result)

	def _get_snake_position(self) -> tuple[int, int]:
		for row in range(self.environment._size):
			for column in range(self.environment._size):
				if self.environment.board[row][column] == self.environment.SNAKE_HEAD:
					return (row, column)
