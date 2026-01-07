import random
import string
from dataclasses import dataclass, field


def generate_id() -> str:
    """
    Generate a random 15-character string of lowercase letters.
    """
    return "".join(random.choices(string.ascii_lowercase, k=15))


@dataclass
class Student:
    """
    A class representing a student.
    """
    name: str
    surname: str
    active: bool = field(default=True)
    login: str = field(init=False)
    id: str = field(init=False)

    def __post_init__(self) -> None:
        """
        Post-initialization method to set default values.
        """
        if self.active:
            if len(self.name) > 0:
                self.login = self.name[0] + self.surname
            else:
                self.login = self.surname
            self.id = generate_id()
        else:
            self.login = "inactive"
            self.id = "inactive"
