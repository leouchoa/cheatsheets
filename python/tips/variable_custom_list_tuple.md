# Using Custom List or Tuples

If you want your `list` or `tuple` to have custom types,
go for the following. For `tuples`:

```python
from typing import TypeAlias

My: TypeAlias = int | str

x: tuple[My, ...]

x = ("a", "b", "a", "b")

y = tuple(x for x in range(5))

z = x + y
```

For `list`:

```python
from typing import TypeAlias

My: TypeAlias = int | str

x: list[My]

x = ["a", "b", "a", "b"]

y = [x for x in range(5)]

z = x + y
```
