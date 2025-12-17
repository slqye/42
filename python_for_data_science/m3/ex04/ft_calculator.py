class calculator:
    """
    Calculator class to perform basic arithmetic operations.
    """

    @staticmethod
    def dotproduct(V1: list[float], V2: list[float]) -> None:
        """
        Dot product operation.
        """
        result: float = sum(V1[i] * V2[i] for i in range(len(V1)))
        print("Dot product is:", result)

    @staticmethod
    def add_vec(V1: list[float], V2: list[float]) -> None:
        """
        Addition operation.
        """
        result: float = [x + y for x, y in zip(V1, V2)]
        print("Add Vector is:", result)

    @staticmethod
    def sous_vec(V1: list[float], V2: list[float]) -> None:
        """
        Subtraction operation.
        """
        result: float = [x - y for x, y in zip(V1, V2)]
        print("Add Vector is:", result)
