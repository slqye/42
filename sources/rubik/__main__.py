from .cube import Cube
from .table import Table
from .shuffle import Shuffle
from .solve import Solve

if __name__ == "__main__":
	cube: Cube = Cube()
	table: Table = Table(cube)

	print("starting table generation")
	table.compute(Table.phase_1, Table.MOVES_G0, "phase_1.table")
	table.compute(Table.phase_2, Table.MOVES_G1, "phase_2.table")
	table.compute(Table.phase_3, Table.MOVES_G2, "phase_3.table")
	table.compute(Table.phase_4, Table.MOVES_G3, "phase_4.table")
