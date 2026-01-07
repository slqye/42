import S1E9 as ex00


class Baratheon(ex00.Character):
    """
    Baratheon class (family) that inherits from Character class.
    """

    def __init__(self, first_name: str, is_alive: bool = True):
        """
        Initialize the Baratheon character with a first name,
        alive status, and family characteristics.
        """
        super().__init__(first_name, is_alive)
        self.family_name = "Baratheon"
        self.eyes = "brown"
        self.hairs = "dark"

    def __repr__(self):
        """
        Return a string representation of the Baratheon character.
        """
        attributes: str = f"('{self.family_name}', \
'{self.eyes}', '{self.hairs}')"

        return (f"{self.__class__.__name__}: {attributes}")

    def __str__(self):
        """
        Return a string representation of the Baratheon character.
        """
        attributes: str = f"('{self.family_name}', \
'{self.eyes}', '{self.hairs}')"

        return (f"{self.__class__.__name__}: {attributes}")

    def die(self) -> None:
        """
        Set the is_alive attribute to False.
        """
        self.is_alive = False


class Lannister(ex00.Character):
    """
    Lannister class (family) that inherits from Character class.
    """

    def __init__(self, first_name: str, is_alive: bool = True):
        """
        Initialize the Lannister character with a first name,
        alive status, and family characteristics.
        """
        super().__init__(first_name, is_alive)
        self.family_name = "Lannister"
        self.eyes = "blue"
        self.hairs = "light"

    def __repr__(self):
        """
        Return a string representation of the Lannister character.
        """
        attributes: str = f"('{self.family_name}', \
'{self.eyes}', '{self.hairs}')"

        return (f"{self.__class__.__name__}: {attributes}")

    def __str__(self):
        """
        Return a string representation of the Lannister character.
        """
        attributes: str = f"('{self.family_name}', \
'{self.eyes}', '{self.hairs}')"

        return (f"{self.__class__.__name__}: {attributes}")

    def die(self) -> None:
        """
        Set the is_alive attribute to False.
        """
        self.is_alive = False

    @staticmethod
    def create_lannister(first_name: str, is_alive: bool = True):
        """
        Create a new Lannister character with a first name
        and alive status.
        """
        return (Lannister(first_name, is_alive))
