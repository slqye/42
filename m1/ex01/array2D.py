import numpy as np


def is_valid_2d_array(value: list) -> bool:
    """
    Check if the input is a valid 2D array (list of lists) and same length.
    """
    first_length: int = 0

    if (not all(isinstance(sublist, list) for sublist in value)):
        return (False)
    first_length = len(value[0])
    return all(len(sublist) == first_length for sublist in value)


def slice_me(family: list, start: int, end: int) -> list:
    """
    Print array shape and return a truncated array based on start and end.
    """
    result: list = None

    if (not isinstance(family, list)):
        print("Error: [family] must be a list")
        return (None)
    if (not isinstance(start, int) or not isinstance(end, int)):
        print("Error: [start] and [end] must be integers")
        return (None)
    result = np.array(family[start:end])
    print("My shape is:", np.array(family).shape)
    print("My new s(hape is:", result.shape)
    return (result)
