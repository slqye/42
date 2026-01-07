def square(x: int | float) -> int | float:
    """
    Square a number.
    """
    return (x * x) if isinstance(x, (int, float)) else None


def pow(x: int | float) -> int | float:
    """
    Raise a number to the power of itslef.
    """
    return (x ** x) if isinstance(x, (int, float)) else None


def outer(x: int | float, function) -> object:
    """
    Outer function that takes a number and a function as arguments.
    """
    count = 0

    def inner() -> float:
        """
        Inner function that applies the given function.
        """
        nonlocal count

        count += 1
        try:
            result = function(x)
            for i in range(count - 1):
                result = function(result)
            return result
        except Exception as e:
            str(e)
            print("ERROR")
    return (inner)
