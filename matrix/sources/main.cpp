#include "commons.hpp"
#include "tests.hpp"

int main(int argc, char **argv)
{
	void (*functions[])(void) = {
		_00,
		_01,
		_02,
		_03,
		_04,
		_05,
		_06,
		_07,
		_08,
		_09,
		_10,
		_11,
		_12,
		_13,
		_14,
		_15,
	};
	std::string function_names[] = {
		"00",
		"01",
		"02",
		"03",
		"04",
		"05",
		"06",
		"07",
		"08",
		"09",
		"10",
		"11",
		"12",
		"13",
		"14",
		"15",
	};

	if (argc != 2)
	{
		std::cerr << "Wrong usage." << std::endl;
		return (1);
	}
	for (unsigned int i = 0; i < sizeof(function_names) / sizeof(function_names[0]); i++)
	{
		if (argv[1] == function_names[i])
		{
			functions[i]();
			return (0);
		}
	}
	std::cerr << "Function not found." << std::endl;
	return (1);
}