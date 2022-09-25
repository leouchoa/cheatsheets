It's a code memory pre-allocation optmization done by the compiler and is the reason why we can use functions in the code before we declare them. In practice javascript is moving all declarations to the top of the scope (which means moving variables and function to the code of code block).

Even tough that is a feature of the javascript language, I think it's wise not to rely on hoisting and declare functions/variables beforehand.

If you still want to rely on hoisting for some things, keep in mind that hoisting with `let` and `const` is different from hoisting with `var`:

- `var`: **are** initialized with a default value of `undefined`
- `let` and `const`: **are not** initialized with a default value of `undefined`

The key concepts to know what's going on here is to keep in mind `declaration` and `initialization`. The first means we allocate a space in memory for the variable while the second means we initialize it with a variable.

The `declaration` and `initialization` behaviours for `let`, `const` and `var` are different. Try it:

- `var`
```
car = 'gol95';
var car;
```

- `let`
```
car = 'gol95';
let car;
```

- `const`
```
car = 'gol95';
const car;
```

# References

- [mdn](https://developer.mozilla.org/en-US/docs/Glossary/Hoisting)
- [w3](https://www.w3schools.com/js/js_hoisting.asp)
