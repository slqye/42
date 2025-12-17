from abc import ABC, abstractmethod


class Character(ABC):
    """
    Abstract Character class that represents a character
    who can be alive or dead.
    """

    def __init__(self, first_name: str, is_alive: bool = True):
        """
        Initialize the character with a first name and
        an alive status.
        """
        self.first_name = first_name
        self.is_alive = is_alive

    def is_alive(self) -> bool:
        """
        Check if the character is alive.
        """
        return (self.is_alive)

    @abstractmethod
    def die(self) -> None:
        """
        Set the is_alive attribute to False.
        """
        pass


class Stark(Character):
    """
    Stark class that inherits from Character class.
    """

    def __init__(self, first_name: str, is_alive: bool = True):
        """
        Initialize the Stark character with a first name
        and an alive status.
        """
        super().__init__(first_name, is_alive)

    def die(self) -> None:
        """
        Set the is_alive attribute to False.
        """
        self.is_alive = False
