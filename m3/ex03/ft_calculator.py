class calculator:
    """
    Calculator class to perform basic arithmetic operations.
    """

    def __init__(self, value: [float | int]) -> None:
        """
        Constructor for calculator class.
        """
        self.value = value

    def __add__(self, object) -> None:
        """
        Addition operation.
        """
        for i in range(len(self.value)):
            self.value[i] += object
        print(self.value)

    def __mul__(self, object) -> None:
        """
        Multiplication operation.
        """
        for i in range(len(self.value)):
            self.value[i] *= object
        print(self.value)

    def __sub__(self, object) -> None:
        """
        Subtraction operation.
        """
        for i in range(len(self.value)):
            self.value[i] -= object
        print(self.value)

    def __truediv__(self, object) -> None:
        """
        Division operation.
        """
        if (object == 0):
            print("Error: Division by zero.")
            return
        for i in range(len(self.value)):
            self.value[i] /= object
        print(self.value)
