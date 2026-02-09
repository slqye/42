import sys
import time

def shell(environment: object, tick: float) -> None:
	sys.stdout.write("\033[H\033[J")
	sys.stdout.write(str(environment))
	sys.stdout.flush()
	time.sleep(tick)
