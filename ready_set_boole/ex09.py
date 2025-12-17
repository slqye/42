import ex03

def check_input(formula: str, sets: [[int]]) -> bool:
	var_count: int = len([1 for x in formula if x.isalpha()])
	null_formula: str = "".join(["0" if x.isalpha() else x for x in formula])

	if (formula == ""):
		return (False)
	if (len(sets) != var_count):
		return (False)
	if (ex03.check_formula(null_formula) == False):
		return (False)
	return (True)

def remove_duplicates(set: [int]) -> [int]:
	return (list(dict.fromkeys(set)))

def handle_not(set: [int], sets: [[int]]) -> [int]:
	univseral_set: [int] = [x for y in sets for x in y]
	value: [int] = [x for x in univseral_set if x not in set]
	return (value)

def handle_and(set_a: [int], set_b: [int]) -> [int]:
	return ([x for x in set_a if x in set_b])

def handle_or(set_a: [int], set_b: [int]) -> [int]:
	return (remove_duplicates([x for x in set_a] + [x for x in set_b]))

def handle_xor(set_a: [int], set_b: [int]) -> [int]:
	value: [int] = [x for x in handle_or(set_a, set_b) if x not in handle_and(set_a, set_b)]
	return (remove_duplicates(value))

def handle_imply(set_a: [int], set_b: [int], sets: [[int]]) -> [int]:
	return (handle_or(handle_not(set_b, sets), set_a))

def handle_equal(set_a: [int], set_b: [int]) -> [int]:
	return ([x for x in set_a if x in set_b])

def eval_set(formula: str, sets: [[int]]) -> [int]:
	stack: [int] = []

	for i in formula:
		if (i.isalpha()):
			stack.append(sets[ord(i) - 65])
		elif (i == "!"):
			stack.append(handle_not(stack.pop(), sets))
		elif (i == "&"):
			stack.append(handle_and(stack.pop(), stack.pop()))
		elif (i == "|"):
			stack.append(handle_or(stack.pop(), stack.pop()))
		elif (i == "^"):
			stack.append(handle_xor(stack.pop(), stack.pop()))
		elif (i == ">"):
			stack.append(handle_imply(stack.pop(), stack.pop(), sets))
		elif (i == "="):
			stack.append(handle_equal(stack.pop(), stack.pop()))
	return (stack[0])

def test(formula: str, sets: [[int]]):
	if (check_input(formula, sets) == False):
		return (print("formula not valid"))
	print(f"eval_set({formula}, {sets}) = {eval_set(formula, sets)}")

if __name__ == "__main__":
	test("A", [[]])
	test("A!", [[]])
	test("A", [[42]])
	test("A!", [[42]])
	test("A!B&", [[1, 2, 3], [2, 3, 4]])
	test("AB|", [[0, 1, 2], []])
	test("AB&", [[0, 1, 2], []])
	test("AB&", [[0, 1, 2], [0]])
	test("AB&", [[0, 1, 2], [42]])
	test("AB^", [[0, 1, 2], [0]])
	test("AB>", [[0], [1, 2]])
	test("AB>", [[0], [0, 1, 2]])
	test("ABC||", [[], [], []])
	test("ABC||", [[0], [1], [2]])
	test("ABC||", [[0], [0], [0]])
	test("ABC&&", [[0], [0], []])
	test("ABC&&", [[0], [0], [0]])
	test("ABC^^", [[0], [0], [0]])
	test("ABC>>", [[0], [0], [0]])
