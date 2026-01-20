import sys
import typer
import rubik

app: typer.Typer = typer.Typer()

@app.command()
def main(input: str) -> None:
	"""
	Solve a Rubik's Cube.
	"""
	cube: rubik.Cube = None

	try:
		cube = rubik.Cube()
		for move in input.split(): cube.spin(move)
		print(f"solution found: {rubik.Solve.thistlethwaite(cube)}")
	except Exception as error:
		print(f"error: {error}", file=sys.stderr)

if __name__ == "__main__":
	app()
