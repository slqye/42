class Node:

	def __init__(self, value: str, left = None, right = None):
		self.value = value
		self.previous = None
		self.left = left
		self.right = right
		self.depth = 0

	def set_previous(self, previous):
		self.previous = previous

	def set_depth(self, depth: int = 0):
		self.depth = depth
		if (self.right): self.right.set_depth(depth + 1)
		if (self.left): self.left.set_depth(depth + 1)

	def __str__(self):
		result: str = ""

		if (self.right):
			result += self.right.__str__()
		result += f"{'	' * self.depth}[{self.value}]\n"
		if (self.left):
			result += self.left.__str__()
		if (self.depth == 0):
			return (result[:-1])
		return (result)

def not_func(value: int):
	if (int(value) == 0): return (1)
	return (0)

def check_formula(formula: str):
	operands: int = 0
	operators: int = 0

	if (len(formula) == 0):
		return (False)
	elif (len(formula) == 1):
		if (formula[0] in "01"):
			return (True)
		else:
			return (False)
	if (formula[0] in "!&|^>=" or formula[1] in "&|^>="):
		return (False)
	for i in formula:
		if (i in "01"): operands += 1
		elif (i in "&|^>="): operators += 1
		elif (i == "!"): operands += 0
		else: return (False)
	if (operators + 1 != operands):
		return (False)
	return (True)

def eval_nodes_formula(node: Node):
	if (node.value in "01"):
		return (int(node.value))
	match node.value:
		case "!": return (bool(not_func(eval_nodes_formula(node.right))))
		case "&": return (bool(eval_nodes_formula(node.right) & eval_nodes_formula(node.left)))
		case "|": return (bool(eval_nodes_formula(node.right) | eval_nodes_formula(node.left)))
		case "^": return (bool(eval_nodes_formula(node.right) ^ eval_nodes_formula(node.left)))
		case ">": return (bool(not_func(eval_nodes_formula(node.right)) | eval_nodes_formula(node.left)))
		case "=": return (bool(not_func(eval_nodes_formula(node.right) ^ eval_nodes_formula(node.left))))

def build_nodes(formula: str):
	stack = []

	if (check_formula(formula) == False):
		return ("Error")
	for i in formula:
		if i in "01":
			stack.append(Node(i, None, None))
		elif i == "!":
			if not stack:
				return ("Error")
			operand = stack.pop()
			stack.append(Node(i, None, operand))
		else:
			if len(stack) < 2:
				return ("Error")
			left = stack.pop()
			right = stack.pop()
			stack.append(Node(i, left, right))
	if len(stack) != 1:
		return ("Error")
	node = stack[0]
	node.set_depth()
	return (node)

def eval_formula(formula: str):
	nodes = build_nodes(formula)
	if (nodes == "Error"):
		return ("Error")
	return (eval_nodes_formula(nodes))

def test(formula: str):
	fn_result: bool = eval_formula(formula)
	title: str = f" eval_formula({formula}) "
	value_result: str = f"result: {fn_result}"
	max_length: int = len(title)
	title_length: int = max_length - len(title)
	result_length: int = len(value_result)

	print(f"╭─{title}{'─' * title_length}─╮")
	print(f"│ {value_result}{' ' * (max_length - result_length)} │")
	print(f"╰─{'─' * max_length}─╯")


if __name__ == "__main__":
    test("10&")
    test("10|")
    test("10|1&")
    test("11>")
    test("10=")
    test("1011||=")
    test("011&|")
    test("010&|")
    test("1|1")
    test("10||")
    test("12|")
    test("10|a")
    test("1!")
    test("0!")
    test("11!&")
    test("10!|")
    test("1!0&")
    test("1!1|")
    test("0!1>")
    test("1!0=")
    test("01|01|&")
    test("11&0|")
    test("10&1|")
    test("11&1|")
    test("11&1|1^")
    test("01&1|1=")
    test("01&1&1&")
    test("0111&&&")
