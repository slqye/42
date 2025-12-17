def ft_tqdm(lst: range) -> None:
    """Print a progress bar for a list of items."""
    percentage: int = 0
    percentage_offset: int = 0
    string_build: str = ""

    for i in lst:
        percentage = round(i * 100 / lst[-1])
        percentage_offset = 3 - len(str(percentage))
        string_build = f"{' ' * percentage_offset}{percentage}%"
        string_build += f"|{'█' * percentage}{' ' * (100 - percentage)}|"
        string_build += f" {i + 1}/{lst[-1] + 1}"
        print(string_build, end="\r")
        yield i
