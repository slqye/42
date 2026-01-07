import sys

if (len(sys.argv) != 1):
	assert len(sys.argv) == 2, "more than one argument is provided"
	if (sys.argv[1][0] == '-'): sys.argv[1] = sys.argv[1][1:]
	assert sys.argv[1].isdigit() == True, "argument is not an integer"
	if (int(sys.argv[1]) % 2 == 0): print("I'm Even.")
	if (int(sys.argv[1]) % 2 != 0): print("I'm Odd.")
