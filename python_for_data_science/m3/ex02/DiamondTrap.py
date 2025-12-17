from S1E7 import Baratheon, Lannister


class King(Baratheon, Lannister):
    """
    Well, its a king, but... From wich family?
    """

    def __init__(self, first_name: str, is_alive: bool = True):
        """
        Constructor for King class.
        """
        super().__init__(first_name, is_alive)
        self.is_alive = is_alive

    def set_eyes(self, eyes: str):
        """
        Set the eyes color of the King.
        """
        self.eyes = eyes

    def set_hairs(self, hairs: str):
        """
        Set the hairs color of the King.
        """
        self.hairs = hairs

    def get_eyes(self):
        """
        Get the eyes color of the King.
        """
        return (self.eyes)

    def get_hairs(self):
        """
        Get the hairs color of the King.
        """
        return (self.hairs)
