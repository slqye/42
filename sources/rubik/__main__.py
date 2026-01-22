from .table import *

if __name__ == "__main__":
	table_0: Table = Table(phase_0, MOVES_G0, debug=True)
	table_1: Table = Table(phase_1, MOVES_G1, debug=True)
	table_2: Table = Table(phase_2, MOVES_G2, debug=True)
	table_3: Table = Table(phase_3, MOVES_G3, debug=True)
	tables: list = [table_0, table_1, table_2, table_3]

	for index, table in enumerate(tables):
		table.compute()
		table.save(f"includes/table_{index}.rubik")
