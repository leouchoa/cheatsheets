# Special Methods

Reference: 

## Binary Operators

| Operator   | Method    |
|--------------- | --------------- |
|`+ ` | `object.__add__(self, other)` |
|`- ` | `object.__sub__(self, other)` |
|`* ` | `object.__mul__(self, other)` |
|`//` | `object.__floordiv__(self, other)` |
|`/ ` | `object.__div__(self, other)` |
|`% ` | `object.__mod__(self, other)` |
|`**` | `object.__pow__(self, other[, modulo])` |
|`<<` | `object.__lshift__(self, other)` |
|`>>` | `object.__rshift__(self, other)` |
|`& ` | `object.__and__(self, other)` |
|`^ ` | `object.__xor__(self, other)` |
|`| ` | `object.__or__(self, other)` |

## Assignment Operators

| Operator   | Method    |
|--------------- | --------------- |
|`+= ` | `object.__iadd__(self, other)` |
|`-= ` | `object.__isub__(self, other)` |
|`*= ` | `object.__imul__(self, other)` |
|`/= ` | `object.__idiv__(self, other)` |
|`//=` | `object.__ifloordiv__(self, other)` |
|`%= ` | `object.__imod__(self, other)` |
|`**=` | `object.__ipow__(self, other[, modulo])` |
|`<<=` | `object.__ilshift__(self, other)` |
|`>>=` | `object.__irshift__(self, other)` |
|`&= ` | `object.__iand__(self, other)` |
|`^= ` | `object.__ixor__(self, other)` |
|`|= ` | `object.__ior__(self, other)` |

# Declaring Type Hints in Separate File


It is possible to declare type hints in a separate file, you just have to append the `.pyi` suffix to it. Example:

```
# person.py file

class Person:
  def __init__(self, name) -> None:
    self.__name = name

  @property
  def name(self) -> str:
    return self.__name
```

Now in a separate `person.pyi` file we just declare the types.

```
# person.pyi file

class Person:
  def __init__(self, name: str) -> None: ...
  def name(self) -> str: ...
```
