# rubik

Hi! This is my 42 cursus project, rubik developed with the help of [Focus](https://github.com/Focuuus).
The objective was to create a 3x3 Rubik's Cube solver that achieves an average solution in 50 moves and under 3 seconds.

## Usage

> [!NOTE]
> To run the program from source, you need to have `uv` installed on your system.
> https://docs.astral.sh/uv/getting-started/installation/

```bash
uv run sources/main.py --help
```

## Explanations

![encoding](assets/encoding.png)

## Ressources

[Thistlethwaite base paper](https://www.jaapsch.net/puzzles/thistle.htm)

[Drew Finnis implementation](https://github.com/dfinnis/Rubik/tree/master)

[Stefan Pochmann implementation](https://www.stefan-pochmann.info/spocc/other_stuff/tools/solver_thistlethwaite/solver_thistlethwaite.txt)

[Quassnoi implementation](https://explainextended.com/2022/12/31/happy-new-year-14/)

[Rohan StackExchange post](https://math.stackexchange.com/questions/1362471/rubiks-cube-thistlethwaite-four-phase-algorithm)

[Tetrad twist explanation](https://puzzling.stackexchange.com/questions/5402/what-is-the-meaning-of-a-tetrad-twist-in-thistlethwaites-algorithm)
