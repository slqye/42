from ctypes import c_uint32 as uint32
import ex02
import ex03
import ex04

def sat(formula: str):
	number: int = ex04.get_var_number(formula)
	possibilities: int = 2 ** number
	formula_var: str = ex04.get_formula_var(formula)
	var_dict: dict = {}
	new_formula: str = ""
	seen: str = ""

	if (ex04.check_formula(formula) == False):
		return (print("formula not valid"))
	for i in range(len(formula_var)):
		var_dict[formula_var[i]] = i
	for i in range(possibilities):
		binary: str = ("{:032b}".format(ex02.gray_code(uint32(i)).value))[32 - number:32]
		new_formula = formula
		seen = ""
		for i in formula:
			if i in "ABCDEFGHIJKLMNOPQRSTUVWXYZ" and i not in seen:
				new_formula = new_formula.replace(i, binary[var_dict[i]])
				seen += i
		if (bool(int(ex03.eval_formula(new_formula))) == True):
			return (True)
	return (False)

def test(formula: str):
	print(f"sat({formula}) = {sat(formula)}")

if __name__ == "__main__":
	test("A")
	test("A!")
	test("AA|")
	test("AA&")
	test("AA!&")
	test("AA^")
	test("AB^")
	test("AB=")
	test("AA>")
	test("AA!>")
	test("ABC||")
	test("AB&A!B!&&")
	test("ABCDE&&&&")
	test("AAA^^")
	test("ABCDE^^^^")
