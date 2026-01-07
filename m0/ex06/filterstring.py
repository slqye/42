import sys


def main(argv: sys.argv) -> None:
    """Main function to call ft_filter.py"""
    assert len(argv) == 3, "wrong number of arguments."
    assert type(argv[1]) is str, "first argument must be a string."
    assert argv[2].isdigit() is True, "second argument must be an uint."
    length: int = int(argv[2])
    print([x for x in argv[1].split() if (lambda x: len(x) > length)(x)])


if __name__ == "__main__":
    main(sys.argv)
