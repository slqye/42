from ex03 import Node as Node
import ex04

def build_var_nodes(formula: str):
	stack = []

	for i in formula:
		if i in "ABCDEFGHIJKLMNOPQRSTUVWXYZ":
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

def copy_node(node):
	if node is None: return None
	new_node = Node(node.value)
	if node.left: new_node.left = copy_node(node.left)
	if node.right: new_node.right = copy_node(node.right)
	return (new_node)

def to_nnf(node: Node):
	new_node: Node = None
	node_left: Node = None
	node_right: Node = None

	if node is None:
		return None
	if node.value == "!":
		match node.right.value:
			case "!":
				return to_nnf(node.right.right)
			case "&":
				node_left = Node("!", None, copy_node(node.right.left))
				node_right = Node("!", None, copy_node(node.right.right))
				new_node = Node("|", node_left, node_right)
				return to_nnf(new_node)
			case "|":
				node_left = Node("!", None, copy_node(node.right.left))
				node_right = Node("!", None, copy_node(node.right.right))
				new_node = Node("&", node_left, node_right)
				return to_nnf(new_node)
			case "^":
				node_left = Node("&", copy_node(node.right.left), copy_node(node.right.right))
				node_right = Node("&", Node("!", None, copy_node(node.right.left)), Node("!", None, copy_node(node.right.right)))
				new_node = Node("|", node_left, node_right)
				return to_nnf(new_node)
			case ">":
				node_left = Node("!", None, copy_node(node.right.left))
				node_right = copy_node(node.right.right)
				new_node = Node("&", node_left, node_right)
				return to_nnf(new_node)
			case "=":
				node_left = Node("|", copy_node(node.right.left), copy_node(node.right.right))
				node_right = Node("|", Node("!", None, copy_node(node.right.left)), Node("!", None, copy_node(node.right.right)))
				new_node = Node("&", node_left, node_right)
				return to_nnf(new_node)
	elif node.value == "^":
		node_left = Node("|", Node("!", None, copy_node(node.left)), Node("!", None, copy_node(node.right)))
		node_right = Node("|", copy_node(node.left), copy_node(node.right))
		new_node = Node("&", node_left, node_right)
		return to_nnf(new_node)
	elif node.value == ">":
		node_left = copy_node(node.left)
		node_right = Node("!", None, copy_node(node.right))
		new_node = Node("|", node_left, node_right)
		return to_nnf(new_node)
	elif node.value == "=":
		node_left = Node("|", Node("!", None, copy_node(node.left)), copy_node(node.right))
		node_right = Node("|", copy_node(node.left), Node("!", None, copy_node(node.right)))
		new_node = Node("&", node_left, node_right)
		return to_nnf(new_node)
	node.left = to_nnf(node.left)
	node.right = to_nnf(node.right)
	return (node)

def to_nnf_string(node: Node):
	if (node == None): return ("")
	if (node.right == None): return (node.value)
	return (to_nnf_string(node.right) + to_nnf_string(node.left) + node.value)

def negation_normal_form(formula: str):
	nnf: Node = None

	if (ex04.check_formula(formula) == False):
		return ((False, "formula is not valid"))
	nnf = to_nnf(build_var_nodes(formula))
	nnf.set_depth()
	return ((True, nnf))

def test(formula: str):
	result: str = negation_normal_form(formula)

	if (result[0] == False): return (print(result[1]))
	print(f"{formula} -> {to_nnf_string(result[1])}")
	ex04.print_truth_table(formula)
	ex04.print_truth_table(to_nnf_string(result[1]))

if __name__ == "__main__":
	test("A")
	test("A!")
	test("AB&!")
	test("AB|!")
	test("AB>!")
	test("AB=!")
	test("ABC||")
	test("ABC||!")
	test("ABC|&")
	test("ABC&|")
	test("ABC&|!")
	test("ABC^^")
	test("ABC>>")
