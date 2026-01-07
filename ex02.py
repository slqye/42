from ctypes import c_uint32 as uint32

def gray_code(n: uint32):
	return (uint32(n.value ^ ( n.value >> 1 )))

def test(a: uint32):
	fn_result: uint32 = gray_code(a) 
	title: str = f" gray_code({a}) "
	bin_a: str = f"bin_a: {'{:032b}'.format(a.value)}"
	value_result: str = f"result: {fn_result.value}"
	bin_result: str = f"bin_r: {'{:032b}'.format(fn_result.value)}"
	max_length: int = len(bin_a)
	title_length: int = max_length - len(title)
	result_length: int = len(value_result)

	print(f"╭─{title}{'─' * title_length}─╮")
	print(f"│ {bin_a} │")
	print(f"│ {' ' * max_length} │")
	print(f"│ {value_result}{' ' * (max_length - result_length)} │")
	print(f"│ {bin_result} │")
	print(f"╰─{'─' * max_length}─╯")


if __name__ == "__main__":
	test(uint32(0))
	test(uint32(1))
	test(uint32(2))
	test(uint32(3))
	test(uint32(4))
	test(uint32(5))
	test(uint32(6))
	test(uint32(7))
	test(uint32(8))
	test(uint32(100))
	test(uint32(65782))
