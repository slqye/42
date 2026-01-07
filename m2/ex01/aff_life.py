import matplotlib.pyplot as plt
import pandas as pd
import load_csv


def main():
    """
    This program show the life_expectancy_years.csv file.
    """
    data: pd.DataFrame = None

    data = load_csv.load("life_expectancy_years.csv")
    if (data is None):
        return
    data = data[data["country"] == "France"]
    data = data.drop(columns="country").T
    data.columns = ["France"]
    plt.figure(figsize=(8, 8))
    plt.plot(data.index, data["France"])
    plt.xlabel("Year")
    plt.ylabel("Life Expectancy")
    plt.title("France Life Expectancy Projections")
    plt.xticks(ticks=data.index[::40])
    plt.tight_layout()
    plt.show()


if __name__ == "__main__":
    main()
