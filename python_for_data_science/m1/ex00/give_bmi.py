import numpy as np


def give_bmi(h: list[int | float], w: list[int | float]) -> list[int | float]:
    """
    Calculate the Body Mass Index (BMI) for a list of heights and weights.
    """
    if (not isinstance(h, list) or not isinstance(w, list)):
        print("Error: [h] and [w] must be lists")
        return (None)
    if (len(h) != len(w)):
        print("Error: [h] and [w] must be the same length")
        return (None)
    if (not all(isinstance(x, (int, float)) for x in h + w)):
        print("Error: [h] and [w] must be numbers")
        return (None)
    return (np.array(w) / np.square(np.array(h)))


def apply_limit(bmi: list[int | float], limit: int) -> list[bool]:
    """
    Return true if the BMI is above the limit, false otherwise.
    """
    if (not all(isinstance(x, (int, float)) for x in bmi + limit)):
        print("Error: [bmi] and [limit] must be numbers")
        return (None)
    return (np.array(bmi) > limit)
