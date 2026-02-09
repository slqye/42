import sys
import abc
import time
import pygame

class IDisplay(abc.ABC):
	def __init__(self, tick: float) -> None:
		self.tick = tick

	@abc.abstractmethod
	def show(self, environment: object) -> None:
		pass

	@abc.abstractmethod
	def close(self) -> None:
		pass

class ShellDisplay(IDisplay):
	def __init__(self, tick: float) -> None:
		super().__init__(tick)

	def show(self, environment: object) -> None:
		sys.stdout.write("\033[H\033[J")
		sys.stdout.write(str(environment))
		sys.stdout.flush()
		time.sleep(self.tick)

	def close(self) -> None:
		print()

class WindowedDisplay(IDisplay):
	WINDOW_SIZE = 500
	BACKGROUND_COLOR = (25, 25, 25)
	WALL_COLOR = (50, 50, 50)
	APPLE_GREEN_COLOR = (100, 200, 100)
	APPLE_RED_COLOR = (200, 100, 100)
	SNAKE_HEAD_COLOR = (50, 50, 200)
	SNAKE_BODY_COLOR = (50, 50, 150)

	def __init__(self, tick: float) -> None:
		super().__init__(tick)
		pygame.init()
		pygame.display.set_caption("learn2slither")

		self.screen = pygame.display.set_mode((self.WINDOW_SIZE, self.WINDOW_SIZE))

	def show(self, environment: object) -> None:
		encoding: dict = environment.board.config["encoding"]
		cell_size: int = self.WINDOW_SIZE / environment.board.config["size"]

		self.screen.fill(self.BACKGROUND_COLOR)
		for row_index, row in enumerate(environment.board.state):
			for col_index, cell in enumerate(row):
				rect: object = (row_index * cell_size, col_index * cell_size, cell_size, cell_size)
				if cell == encoding["wall"]:
					pygame.draw.rect(self.screen, self.WALL_COLOR, rect)
				elif cell == encoding["apple_green"]:
					pygame.draw.rect(self.screen, self.APPLE_GREEN_COLOR, rect)
				elif cell == encoding["apple_red"]:
					pygame.draw.rect(self.screen, self.APPLE_RED_COLOR, rect)
				elif cell == encoding["snake_head"]:
					pygame.draw.rect(self.screen, self.SNAKE_HEAD_COLOR, rect)
				elif cell == encoding["snake_body"]:
					pygame.draw.rect(self.screen, self.SNAKE_BODY_COLOR, rect)
		pygame.display.flip()
		pygame.time.wait(round(self.tick * 1000))

	def close(self) -> None:
		pygame.quit()
