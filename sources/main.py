import sys
import time
import typer
import rubik
from typing import Optional
from typing_extensions import Annotated

app: typer.Typer = typer.Typer()

def run_benchmark(iterations: int) -> None:
	"""
	Run benchmark and display statistics.
	"""
	print(f"🏁 Starting benchmark with {iterations} iterations...\n")
	move_counts = []
	times = []
	for i in range(iterations):
		cube = rubik.Cube()
		shuffle = rubik.Shuffle.random(rubik.Cube.SPINS)
		cube.spin_sequence(rubik.Solve.regroup_moves(shuffle))
		start_time = time.time()
		solution = rubik.Solve.thistlethwaite(cube)
		end_time = time.time()
		move_count = len(solution.split())
		elapsed = end_time - start_time
		move_counts.append(move_count)
		times.append(elapsed)
		print(f"\r⏳ Progress: {i + 1}/{iterations}", end='', flush=True)
	print(f"\n============================")
	print(f"📈 BENCHMARK RESULTS")
	print(f"============================")
	print(f"🎯 MOVE:")
	print(f"   ├─ Best:    {min(move_counts)} moves")
	print(f"   ├─ Worst:   {max(move_counts)} moves")
	print(f"   ├─ Average: {sum(move_counts)/len(move_counts):.2f} moves")
	print(f"   └─ Total:   {sum(move_counts)} moves\n")
	print(f"⚡ TIME:")
	print(f"   ├─ Fastest:  {min(times):.5f}s")
	print(f"   ├─ Slowest:  {max(times):.5f}s")
	print(f"   ├─ Average:  {sum(times)/len(times):.5f}s")
	print(f"   └─ Total:    {sum(times):.5f}s")
	print(f"============================")

@app.command()
def main(
	moves: Annotated[Optional[str], typer.Argument()] = None,
	random: Annotated[bool, typer.Option("--random", "-r")] = False,
	length: Annotated[Optional[int], typer.Option("--length", "-l")] = None,
	debug: Annotated[bool, typer.Option("--debug", "-d")] = False,
	count_moves: Annotated[bool, typer.Option("--count-moves", "-c")] = False,
	show_time: Annotated[bool, typer.Option("--time", "-t")] = False,
	benchmark: Annotated[Optional[int], typer.Option("--benchmark", "-b")] = None) -> None:
	"""
	Solve a Rubik's Cube.
	"""
	try:
		if benchmark:
			return run_benchmark(benchmark)
		cube = rubik.Cube()
		if debug:
			cube._debug = True
		if moves:
			shuffle = moves
		elif length is not None:
			shuffle = rubik.Shuffle.custom(rubik.Cube.SPINS, length)
		elif random:
			shuffle = rubik.Shuffle.random(rubik.Cube.SPINS)
		else:
			shuffle = rubik.Shuffle.random(rubik.Cube.SPINS)
		print(f"🎲 Shuffle: [{shuffle}]")
		if count_moves:
			shuffle_count = len([m for m in rubik.Solve.space_moves(rubik.Solve.regroup_moves(shuffle)).split()])
			print(f"🔢 Shuffle moves: {shuffle_count}")
		cube.spin_sequence(rubik.Solve.regroup_moves(shuffle))
		start_time = time.time()
		solution = rubik.Solve.thistlethwaite(cube)
		end_time = time.time()
		print(f"💡 Sequence to solve: [{solution}]")
		if count_moves:
			solution_count = len(solution.split())
			print(f"📊 Solution moves: {solution_count}")
		if show_time:
			elapsed = end_time - start_time
			print(f"⏱️  Execution time: {elapsed:.6f}s")
	except Exception as error:
		print(f"error: {error}", file=sys.stderr)

if __name__ == "__main__":
	app()
