import sys
import typer
import rubik

app: typer.Typer = typer.Typer()

@app.command()
def main(input: str) -> None:
	"""
	Cli entry to solve a Rubik's Cube.
	"""
	cube: rubik.cube.Cube = None

	try:
		cube = rubik.cube.Cube()
		for move in input.split(): cube.spin(move)
		print(" ".join(rubik.solve.thistlethwaite(cube)))
	except Exception as error:
		print(f"error: {error}", file=sys.stderr)

if __name__ == "__main__":
	app()
