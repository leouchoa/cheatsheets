# Type Hinting

## Generic Type vs Any type

Here the discussion is about the difference between using `Any` and `TypeVar("T")`.
Consider the code bellow:

```python
def process_elements(elements: <TYPE_HERE>) -> <TYPE_HERE>:
    return [element for index,element in enumerate(elements) if index % 2 == 1]
```

If `<TYPE_HERE>` is `list[TypeVar("T")]`, what you're saying is that if you input
a box of apples the output will be a box apples. It maybe sliced or even grounded
apples, but it will be apples.

By contrast, if `<TYPE_HERE>` is `list[Any]`, what you're saying is that if you
input a box of apples, the output may not be a box of apples, it may be a box of
oranges even if they are sliced or grounded. The function will work anyway, but
the underlaying content may be different.
