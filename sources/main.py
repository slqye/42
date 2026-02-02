import r_learn.agent as rl_agent
import r_learn.environment as rl_env

def main():
	configuration: object = rl_env.Snake.Configuration((10, 10), 2, 1, rl_agent.Basic())
	board = rl_env.Snake(configuration)

if __name__ == "__main__":
	main()
