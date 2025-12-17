import sys

def get_training_output() -> tuple[float, float]:
	"""
	Reads slope and intercept from "training.out".
	"""
	try:
		with open("training.out", "r", encoding="utf-8") as file:
			lines: list[str] = file.readlines()
			slope: float = float(lines[0])
			intersect: float = float(lines[1])
			return (slope, intersect)
	except FileNotFoundError:
		return (0, 0)
	except Exception as error:
		print("Error:", error, file=sys.stderr)
		sys.exit(1)

def main():
	"""
	Calculates and displays the estimated car price
	based on mileage using a linear regression model.
	"""
	try:
		function: tuple[float, float] = get_training_output()
		mileage: int = int(input("Car mileage: "))

		if mileage < 0:
			raise ValueError("the mileage can't be negative")
		result: float = function[0] * mileage + function[1]
		result = 0 if result < 0 else result
		print(f"The estimated price is: {result:.2f}$")
	except Exception as error:
		print("Error:", error, file=sys.stderr)
		sys.exit(1)


if __name__ == "__main__":
	main()
