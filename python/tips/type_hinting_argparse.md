# Type Hinting Argparse

```python
import argparse


class ParseHints(argparse.Namespace):
    """docstring for ParseHints."""

    def __init__(
        self,
    ):
        super(ParseHints, self).__init__()
        self.my_param = "dft_val"


def main(args: ParseHints):
    """todo"""
    print(args.my_param)


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="your description")

    _ = parser.add_argument(
        "--my_param",
        type=str,
        help="param help doc",
    )

    nsp = ParseHints()

    args = parser.parse_args(namespace=nsp)
    print(args)

    main(args)

```
