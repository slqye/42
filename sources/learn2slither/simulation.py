import sys
import time

def shell(agent: object, environment: object, tick: float) -> None:
	for _ in agent.play(environment):
		sys.stdout.write("\033[H\033[J")
		sys.stdout.write(str(environment))
		sys.stdout.flush()
		time.sleep(tick)
	print()
