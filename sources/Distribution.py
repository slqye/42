import sys
import os
import matplotlib.pyplot as plt
import seaborn as sns
import pandas as pd
import typer


def get_plant_types(directory: str) -> dict:
    """
    return a dictionary of global type containing
    array of subtype with theire number.
    """
    plant_types: dict = {}

    for (root, _, files) in os.walk(directory):
        plant_type_full: str = root[root.rfind("/") + 1:].lower()
        plant_type: str = plant_type_full[:plant_type_full.find("_")].lower()
        if plant_type == "":
            continue
        if plant_type not in plant_types:
            plant_types[plant_type] = [(plant_type_full, len(files))]
        else:
            plant_types[plant_type].append((plant_type_full, len(files)))
    return plant_types


def plot_plant_type(item: tuple) -> None:
    """
    Plot plant's subtypes using matplotlib and seaborn.
    """
    sns.set_theme()
    fig, (ax1, ax2) = plt.subplots(1, 2, figsize=(12, 6))
    ax1.pie(
        x=[x[1] for x in item[1]],
        labels=[x[0] for x in item[1]],
        autopct="%1.1f%%"
    )
    barplot_df: pd.DataFrame = pd.DataFrame(
        item[1],
        columns=["subtype", "quantity"]
    )
    sns.barplot(
        x="subtype",
        y="quantity",
        data=barplot_df,
        hue="subtype",
        ax=ax2
    )
    plt.suptitle(f"{item[0]} class distribution")
    plt.tight_layout()
    plt.show()


def main(directory: str) -> None:
    """
    Analyze a directory of images with plots.
    """
    plant_types: dict = {}

    if not os.path.isdir(directory):
        raise ValueError("wrong type of argument.")
    plant_types = get_plant_types(directory)
    for item in plant_types.items():
        plot_plant_type(item)


if __name__ == "__main__":
    try:
        typer.run(main)
        main(sys.argv)
    except Exception as error:
        print(f"error: {error}", file=sys.stderr)
