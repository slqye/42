from ctypes import c_uint32 as uint32
import ex02
import ex03

def get_var_number(formula: str):
	result: int = 0
	double_var: str = ""

	for i in formula:
		if i in "ABCDEFGHIJKLMNOPQRSTUVWXYZ" and i not in double_var:
			result += 1
			double_var += i
	return (result)

def check_formula(formula: str):
	new_formula: str = ""

	for i in formula:
		if i in "ABCDEFGHIJKLMNOPQRSTUVWXYZ":
			new_formula += "0"
		else:
			new_formula += i
	if (ex03.eval_formula(new_formula) == "Error"):
		return (False)
	return (True)

def count_var_index(formula: str, var: str):
	count: int = 0
	double_var: str = ""

	for i in formula:
		if i in "ABCDEFGHIJKLMNOPQRSTUVWXYZ" and i not in double_var:
			if (i == var):
				return (count)
			double_var += i
			count += 1
	return (-1)

def get_formula_var(formula: str):
	result: str = ""

	for i in formula:
		if i in "ABCDEFGHIJKLMNOPQRSTUVWXYZ" and i not in result:
			result += i
	return ("".join(sorted(result)))

def print_truth_table(formula: str):
	number: int = get_var_number(formula)
	possibilities: int = 2 ** number
	formula_var: str = get_formula_var(formula)
	var_dict: dict = {}
	seen: str = ""

	if (check_formula(formula) == False):
		return (print("formula not valid"))
	print(f"╭{'─' * (((number + 1) * 2) + 1)}╮")
	print("│", end="")
	for i in formula_var:
		print(f" {i}", end="")
	print(" = │")
	for i in range(len(formula_var)):
		var_dict[formula_var[i]] = i
	for i in range(possibilities):
		print("│", end="")
		binary_str = ("{:032b}".format(ex02.gray_code(uint32(i)).value))[32 - number:32]
		for i in binary_str:
			print(f" {i}", end="")
		new_formula: str = formula
		seen = ""
		for i in formula:
			if i in "ABCDEFGHIJKLMNOPQRSTUVWXYZ" and i not in seen:
				new_formula = new_formula.replace(i, binary_str[var_dict[i]])
				seen += i
		print(f" {int(ex03.eval_formula(new_formula))} │")
	print(f"╰{'─' * (((number + 1) * 2) + 1)}╯")

if __name__ == "__main__":
	print_truth_table("A")
	print_truth_table("A!")
	print_truth_table("AB|")
	print_truth_table("AB&")
	print_truth_table("AB^")
	print_truth_table("AB>")
	print_truth_table("AB=")
	print_truth_table("AA=")
	print_truth_table("ABC==")
	print_truth_table("AB>C>")
	print_truth_table("AB>A>A>")
