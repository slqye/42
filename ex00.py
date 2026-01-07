from ctypes import c_uint32 as uint32

def half_adder(a: uint32, b: uint32):
	return ((uint32(a.value & b.value), uint32(a.value ^ b.value)))

def adder(a: uint32, b: uint32):
	result: uint32 = uint32(0)
	byte_a: uint32 = uint32(0)
	byte_b: uint32 = uint32(0)
	mask: uint32 = uint32(1)
	carry: uint32 = uint32(0)
	position: int = 0

	while (a.value != 0 or b.value != 0 or carry.value != 0):
		byte_a = uint32(a.value & mask.value)
		byte_b = uint32(b.value & mask.value)
		carry_1, sum_1 = half_adder(byte_a, byte_b)
		carry_2, sum_2 = half_adder(sum_1, carry)
		carry = uint32(carry_1.value | carry_2.value)
		result = uint32(result.value | (sum_2.value << position))
		a = uint32(a.value >> 1)
		b = uint32(b.value >> 1)
		position += 1
	return (result)

def test(a: uint32, b: uint32):
	fn_result: uint32 = adder(a, b)
	title: str = f" {a} + {b} "
	bin_a: str = f"bin_a: {'{:032b}'.format(a.value)}"
	bin_b: str = f"bin_b: {'{:032b}'.format(b.value)}"
	value_result: str = f"result: {fn_result.value}"
	bin_result: str = f"bin_r: {'{:032b}'.format(fn_result.value)}"
	max_length: int = len(bin_a)
	title_length: int = max_length - len(title)
	result_length: int = len(value_result)

	print(f"╭─{title}{'─' * title_length}─╮")
	print(f"│ {bin_a} │")
	print(f"│ {bin_b} │")
	print(f"│ {' ' * max_length} │")
	print(f"│ {value_result}{' ' * (max_length - result_length)} │")
	print(f"│ {bin_result} │")
	print(f"╰─{'─' * max_length}─╯")


if __name__ == "__main__":
	test(uint32(0), uint32(0))
	test(uint32(1), uint32(0))
	test(uint32(0), uint32(1))
	test(uint32(1), uint32(1))
	test(uint32(1), uint32(2))
	test(uint32(2), uint32(2))
	test(uint32(0), uint32(2))
	test(uint32(2), uint32(0))
	test(uint32(42), uint32(42))
	test(uint32(378), uint32(489))
	test(uint32(4294967295), uint32(0))
	test(uint32(4294967295), uint32(1))
	test(uint32(4294967295), uint32(2))
	test(uint32(4294967295), uint32(200))
	test(uint32(-1), uint32(1))
