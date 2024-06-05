# Special Methods

## Declaring Type Hints in Separate File

It is possible to declare type hints in a separate file, you just have to append
the `.pyi` suffix to it. Example:

```python
# person.py file

class Person:
  def __init__(self, name) -> None:
    self.__name = name

  @property
  def name(self) -> str:
    return self.__name
```

Now in a separate `person.pyi` file we just declare the types.

```python
# person.pyi file

class Person:
  def __init__(self, name: str) -> None: ...
  def name(self) -> str: ...
```

## Templating Using Jinja

- [excelent resource](https://ttl255.com/jinja2-tutorial-part-1-introduction-and-variable-substitution/)
- [cool jinja2 alternative api doc](https://tedboy.github.io/jinja2/templ1.html)
