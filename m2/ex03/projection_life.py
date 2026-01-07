import matplotlib.pyplot as plt
import pandas as pd
import load_csv


def main():
    """
    This program show the population_total.csv file.
    """
    file_1: str = "income_per_person_gdppercapita_ppp_inflation_adjusted.csv"
    file_2: str = "life_expectancy_years.csv"
    data_1: pd.DataFrame = None
    data_2: pd.DataFrame = None

    data_1 = load_csv.load(file_1)
    data_2 = load_csv.load(file_2)
    if (data_1 is None or data_2 is None):
        return
    plt.scatter(data_1["1900"], data_2["1900"])
    plt.title("1900")
    plt.xlabel("Gross Domestic Product")
    plt.ylabel("Life Expectancy")
    plt.xscale("log")
    plt.show()


if __name__ == "__main__":
    main()
