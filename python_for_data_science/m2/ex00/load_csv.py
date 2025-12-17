import pandas as pd


def load(path: str) -> pd.DataFrame:
    """
    Load a CSV file into a pandas DataFrame.
    """
    result: pd.DataFrame = None

    try:
        result = pd.read_csv(path)
        print("Loading dataset of dimensions", result.shape)
        print(result)
        return (result)
    except Exception as e:
        print("Error:", e)
        return (None)
