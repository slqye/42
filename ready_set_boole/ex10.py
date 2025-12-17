MAX_INDEX: int = 2**32 - 1
MAX_VALUE: int = 2**16 - 1

def map(x: int, y: int) -> float:
	index = x * (MAX_VALUE + 1) + y
	normalized_index = index / MAX_INDEX
	return (normalized_index)

def test(x: int, y: int):
	if (x < 0 or x > MAX_VALUE): return (print(f"x must be between 0 and {MAX_VALUE}"))
	if (y < 0 or y > MAX_VALUE): return (print(f"y must be between 0 and {MAX_VALUE}"))
	print(f"map{x, y} = {map(x, y)}")

if __name__ == "__main__":
	test(0, 0)
	test(2**16 - 1, 2**16 - 1)
	test(32767, 65535)
	test(2, 3)
	test(3, 2)
	test(456, 2547)
	test(12, 7852)
	test(-2, 1)
	test(MAX_VALUE + 1, 1)
