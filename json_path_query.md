# How to Query From Json

You can something called [jpath](https://www.ibm.com/docs/en/dsm?topic=protocol-jpath).

Suppose you have an array like this:

```json
[
    1,
    2,
    3,
    4,
    5,
    6,
    7,
    8,
    9,
    10
]
```

If you want to filter what items are bigger than 5, you use `$[?(@>40)]`,
where:

- `$` is the root of the document.
- `?` means a filtering operation
- `@` is because this list has no name.

For more basic functions, check out those links:

- [IBM Functions in JPath expressions](https://www.ibm.com/docs/en/dsm?topic=jpath-functions-in-expressions)
- [Free Kodekloud jpath course](https://kodekloud.com/courses/json-path-quiz/)
