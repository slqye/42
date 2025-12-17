def powerset(set: [int]) -> [int]:
	result: [int] = [[]]

	for i in set:
		result += [x + [i] for x in result]
	return (result)

def test(set: [int]):
	print(f"powerset({set}) = {powerset(set)}")

if __name__ == "__main__":
    test([])
    test([0])
    test([0, 1])
    test([0, 1, 2])
    test([0, 1, 2, 3])
