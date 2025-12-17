def ft_statistics(*args: any, **kwargs: any) -> None:
    """
    This function calculates the mean, median, quartiles,
    standard deviation, or variance of a given dataset.
    """
    for kwarg in kwargs.values():
        try:
            match kwarg:
                case "mean":
                    print("mean:", sum(args) / len(args))
                case "median":
                    v_sorted: list = sorted(args)
                    v_len: int = len(v_sorted)
                    if (len(args) % 2 == 0):
                        first = v_sorted[v_len / 2 - 1]
                        second = v_sorted[v_len / 2]
                        print("median:", (first + second) / 2)
                    else:
                        print("median:", v_sorted[v_len // 2])
                case "quartile":
                    v_sorted: list = sorted(args)
                    v_len: int = len(v_sorted)
                    q1 = v_sorted[int(v_len * 1 / 4)]
                    q3 = v_sorted[int(v_len * 3 / 4)]
                    print("quartile:", [q1, q3])
                case "std":
                    mean = sum(args) / len(args)
                    upper = sum((x - mean) ** 2 for x in args)
                    lower = upper / len(args)
                    print("std:", lower ** 0.5)
                case "var":
                    mean = sum(args) / len(args)
                    upper = sum((x - mean) ** 2 for x in args)
                    print("var:", upper / len(args))
        except Exception as e:
            str(e)
            print("ERROR")
