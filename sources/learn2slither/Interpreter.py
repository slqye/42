import abc

class IInterpreter(abc.ABC):
	@staticmethod
	@abc.abstractmethod
	def compute_state(environment: object) -> str:
		pass

class SnakeInterpreter(IInterpreter):
	@staticmethod
	def compute_state(environment: object) -> str:
		snake_position: tuple[int, int] = environment.snake.position
		row: list[str] = environment.board.state[snake_position[0]]
		column: list[str] = [row[snake_position[1]] for row in environment.board.state]
		visions: list[str] = [
			row[:snake_position[1]][::-1],
			column[:snake_position[0]][::-1],
			row[snake_position[1] + 1:],
			column[snake_position[0] + 1:]
		]
		result: list = []

		result.append(row[snake_position[1] - 1])
		result.append(str(SnakeInterpreter._get_reward_farness(environment, visions[0])))
		result.append(column[snake_position[0] - 1])
		result.append(str(SnakeInterpreter._get_reward_farness(environment, visions[1])))
		result.append(row[snake_position[1] + 1])
		result.append(str(SnakeInterpreter._get_reward_farness(environment, visions[2])))
		result.append(column[snake_position[0] + 1])
		result.append(str(SnakeInterpreter._get_reward_farness(environment, visions[3])))
		return "".join(result)

	@staticmethod
	def _get_reward_farness(environment: object, vision: str) -> int:
		farness: int = 0
		step = round(environment.config["board"]["size"] / 3)

		for index, cell in enumerate(vision):
			if cell == environment.config["board"]["encoding"]["apple_green"]:
				farness = index + 1
				break
		for index in range(2):
			if farness > index * step and farness <= (index + 1) * step:
				return index + 1
		if farness != 0:
			return 3
		return farness
