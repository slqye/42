import matplotlib.pyplot as plt
import pandas as pd
import load_csv


def convert_population(value):
    """
    Convert population values from string to int.
    """
    if isinstance(value, str):
        if value.endswith("M"):
            return float(value[:-1]) * 1_000_000
        elif value.endswith("k"):
            return float(value[:-1]) * 1_000
        else:
            return float(value)
    return value


def main():
    """
    This program show the population_total.csv file.
    """
    data: pd.DataFrame = None

    data = load_csv.load("population_total.csv")
    if (data is None):
        return
    data = data[data["country"].isin(["France", "Belgium"])]
    data = data.set_index("country").T
    data = data.map(convert_population)
    data.index = data.index.astype(int)
    plt.figure(figsize=(8, 8))
    plt.plot(data.index, data["France"], label="France")
    plt.plot(data.index, data["Belgium"], label="Belgium")
    plt.xlabel("Year")
    plt.ylabel("Population")
    plt.title("Pupulation Projection")
    plt.xticks(ticks=data.index[::40])
    plt.xlim(1800, 2050)
    plt.tight_layout()
    plt.legend()
    plt.show()


if __name__ == "__main__":
    main()
