# Hoisting

It's a code memory pre-allocation optmization done by the compiler and is the
reason why we can use functions in the code before we declare them.
In practice javascript is moving all declarations to the top of the scope
(which means moving variables and function to the code of code block).

Even tough that is a feature of the javascript language, I think it's wise not
to rely on hoisting and declare functions/variables beforehand.

If you still want to rely on hoisting for some things, keep in mind that hoisting
with `let` and `const` is different from hoisting with `var`:

- `var`: **are** initialized with a default value of `undefined`

- `let` and `const`: **are not** initialized with a default value of `undefined`

The key concepts to know what's going on here is to keep in mind `declaration`
and `initialization`. The first means we allocate a space in memory for the
variable while the second means we initialize it with a variable.

Example: in the following the value of `freezing` is `undefined`.

```js
function getClothing(isCold) {
  if (isCold) {
    var freezing = 'Grab a jacket!';
  } else {
    var hot = 'It’s a shorts kind of day.';
    console.log(freezing);
  }
}
```

In practice, this is what javascript does:

```js
function getClothing(isCold) {
  var freezing, hot;
  if (isCold) {
    freezing = 'Grab a jacket!';
  } else {
    hot = 'It’s a shorts kind of day.';
    console.log(freezing);
  }
}
```

The solution is to use `let` and `const`, because they’re scoped to the block,
not to the function. If a variable is declared using `let` or `const` inside a block
of code (denoted by curly braces `{ }`), then the variable is stuck in what is
known as the **temporal* dead* zone until the variable’s declaration is processed.
This behavior prevents variables from being accessed only until after they’ve
been declared.

## Rule of thumb for when to use `let` vs `const`

- Variables declared with `let` can be reassigned, but can’t be redeclared in
  the same scope.
- Variables declared with `const` must be assigned an initial value, but can’t
  be redeclared in the same scope, and can’t be reassigned.

- Use `let` when you plan to reassign new values to a variable, and
- Use `const` when you don’t plan on reassigning new values to a variable.

Since `const` is the strictest way to declare a variable, use `const` as the
default way to declare your variables, because it'll make your code easier to
reason about since you know the identifiers won't change throughout the lifetime
of your program. If you find that you need to update a variable or change it,
then go back and switch it from `const` to `let`.

## Is there any reason to use var anymore?

**Not really.**

There are some arguments that can be made for using `var` in situations where you
want to globally define variables, but this is often considered bad practice
and should be avoided.

## References

- [mdn](https://developer.mozilla.org/en-US/docs/Glossary/Hoisting)
- [w3](https://www.w3schools.com/js/js_hoisting.asp)
