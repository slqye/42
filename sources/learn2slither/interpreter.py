import abc

class Interpreter(abc.ABC):
	@abc.abstractmethod
	def compute_state(environment: object) -> str:
		pass

class SnakeInterpreter(Interpreter):
	@staticmethod
	def compute_state(environment: object) -> str:
		snake_position: tuple[int, int] = environment.snake.position
		row: list[str] = environment.board.state[snake_position[0]]
		column: list[str] = [row[snake_position[1]] for row in environment.board.state]
		result: list  = []

		result.append(row[snake_position[1] - 1])
		result.append(column[snake_position[0] - 1])
		result.append(row[snake_position[1] + 1])
		result.append(column[snake_position[0] + 1])
		return "".join(result)
