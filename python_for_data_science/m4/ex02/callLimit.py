def callLimit(limit: int):
    """
    Decorator to limit the number of times a function can be called.
    """
    count = 0

    def callLimiter(function):
        """
        Decorator function that limits the number of calls to a function.
        """

        def limit_function(*args: any, **kwds: any):
            """
            Inner function that checks the count value.
            """
            nonlocal count
            if count < limit:
                count += 1
                return (function(*args, **kwds))
            else:
                print(f"Error: {function} call too many times")
                return (None)
        return (limit_function)
    return (callLimiter)
