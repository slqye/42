from ctypes import c_uint32 as uint32
import ex00

def minus_one(v: uint32):
	result: uint32 = v
	byte: uint32 = uint32(0)
	position: int = 0

	while (v.value != 0):
		byte = uint32(v.value & 1)
		if (byte.value == 0):
			result = uint32(result.value | (1 << position))
		else:
			result = uint32(result.value ^ (1 << position))
			return (result)
		v = uint32(v.value >> 1)
		position += 1
	return (result)

def multiplier(a: uint32, b: uint32):
	if (b.value == 0):
		return (uint32(0))
	return (ex00.adder(multiplier(a, minus_one(b)), a))

def multiplier_bis(a: uint32, b: uint32):
	result: uint32 = uint32(0)

	while (b.value > 0):
		result = ex00.adder(result, a)
		b = minus_one(b)
	return (result)

def test(a: uint32, b: uint32, multiplier_func):
	fn_result: uint32 = multiplier_func(a, b)
	title: str = f" {a} * {b} "
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
	test(uint32(0), uint32(0), multiplier)
	test(uint32(1), uint32(1), multiplier)
	test(uint32(0), uint32(2), multiplier)
	test(uint32(2), uint32(0), multiplier)
	test(uint32(2), uint32(2), multiplier)
	test(uint32(42), uint32(42), multiplier)
	test(uint32(378), uint32(489), multiplier)
	test(uint32(4294967295), uint32(1), multiplier)
	test(uint32(4294967295), uint32(2), multiplier)
	test(uint32(4294967295), uint32(10), multiplier)
	
	# Additional tests using multiplier_bis
	print("\nTesting multiplier_bis function:")
	test(uint32(0), uint32(0), multiplier_bis)
	test(uint32(1), uint32(1), multiplier_bis)
	test(uint32(0), uint32(2), multiplier_bis)
	test(uint32(2), uint32(0), multiplier_bis)
	test(uint32(2), uint32(2), multiplier_bis)
	test(uint32(42), uint32(42), multiplier_bis)
	test(uint32(378), uint32(489), multiplier_bis)
	test(uint32(4294967295), uint32(1), multiplier_bis)
	test(uint32(4294967295), uint32(2), multiplier_bis)
	test(uint32(4294967295), uint32(10), multiplier_bis)
