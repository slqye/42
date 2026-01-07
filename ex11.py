MAX_INDEX: int = 2**32 - 1
MAX_VALUE: int = 2**16 - 1

def reverse_map(n: float) -> (int, int):
	a = n * MAX_INDEX
	x = int(a // (MAX_VALUE + 1))
	y = int(a % (MAX_VALUE + 1))
	return ((x, y))

def test(n: float):
	if (n < 0 or n > 1): return (print("n must be between 0 and 1"))
	print(f"reverse_map({n}) = {reverse_map(n)}")

if __name__ == "__main__":
	test(0)
	test(1)
	test(0.5)
	test(3.051827662403655e-05)
	test(4.577683285944556e-05)
	test(0.006958600833769562)
	test(0.0001849336550070284)
	test(-0.2)
	test(1.3)
