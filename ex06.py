from ex03 import Node as Node
import ex04
import ex05

def flatten_and(node: Node):
	if (node.value == "&"):
		return (flatten_and(ex05.copy_node(node.left)) + flatten_and(ex05.copy_node(node.right)))
	return ([node])

def to_cnf(node: Node):
	if (node is None):
		return None
	node.left = to_cnf(node.left)
	node.right = to_cnf(node.right)
	if (node.value == "&"):
		return (Node("&", node.left, node.right))
	elif (node.value == "|"):
		if (node.left is not None and node.left.value == "&"):
			new_left = Node("|", ex05.copy_node(node.left.left), ex05.copy_node(node.right))
			new_right = Node("|", ex05.copy_node(node.left.right), ex05.copy_node(node.right))
			result = Node("&", new_left, new_right)
			return to_cnf(result)
		elif (node.right is not None and node.right.value == "&"):
			new_left = Node("|", ex05.copy_node(node.left), ex05.copy_node(node.right.left))
			new_right = Node("|", ex05.copy_node(node.left), ex05.copy_node(node.right.right))
			result = Node("&", new_left, new_right)
			return to_cnf(result)
	return (node)

def to_cnf_string(value: str):
	and_count: int = value.count("&")
	result: str = ""

	for i in value:
		if (i != "&"):
			result += i
	result += and_count * "&"
	return (result)

def test(formula: str):
	nnf: str = ex05.negation_normal_form(formula)

	if (nnf[0] == False): return (print(nnf[1]))
	cnf: Node = to_cnf(nnf[1])
	cnf.set_depth()
	result: str = ex05.to_nnf_string(cnf)
	print(f"{formula} -> {to_cnf_string(result)}")
	ex04.print_truth_table(formula)
	ex04.print_truth_table(result)

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
	test("AB|C&")
	test("AB|C|D|")
	test("AB&C&D&")
	test("AB&!C!|")
	test("AB|!C!&")
	test("CD&AB&|")

