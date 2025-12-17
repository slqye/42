import sys


def main(args) -> None:
    """Main function that give informations about a string"""
    punctuation = '''!()-[]{};:'"\\,<>./?@#$%^&*_~'''
    value: str = ""

    assert len(args) <= 2, "wrong number of arguments."
    if (len(args) == 1):
        print("What is the text to count?")
        value = sys.stdin.readline()
    else:
        value = args[1]
    spaces: int = value.count(' ') + value.count('\n')
    print(f"The text contains {len(value)} characters:")
    print(f"{sum(i.isupper() for i in value)} upper letters")
    print(f"{sum(i.islower() for i in value)} lower letters")
    print(f"{sum(i in punctuation for i in value)} punctuation marks")
    print(f"{spaces} spaces")
    print(f"{sum(i.isdigit() for i in value)} digits")


if __name__ == "__main__":
    main(sys.argv)
