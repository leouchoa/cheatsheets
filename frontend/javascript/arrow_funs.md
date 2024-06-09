# Arrow Functions

Regular functions can be either function declarations or function expressions,
however arrow functions are always expressions. This means:

- arrow functions are only expressions

- there's no such thing as an arrow function declaration.

In fact, their full name is "arrow function expressions", so they can only be
used where an expression is valid. This includes being:

- Stored in a variable,
- Passed as an argument to a function,
- Stored in an object's property.

About params:

- Single parameter works with and without parentheses.
- Multiple parameters requires parentheses.

Also:

- If an arrow function has curly braces and no return, it will run, but nothing
gets returned.

- If an arrow function doesn't use curly braces, it is using the concise syntax
and it will automatically return the expression. It should not have a `return` keyword.

## Single args function

```js
a => a + 10; // equivalent to (a) => a + 10;
```

## If multiline, need to add a `return`

```js
a => {
  const b = 10;
  return a + b;
}
```

## Void function

```js
const x = 100;
() => {
  const a = x*2;
  return a + x;
}
```

```js
() => a + b + 10;
```

```js
const sayHi = () => console.log('Hello!');
sayHi();
```

## Underscore as Void Function Name

You can use the underscore `_` instead of parenthesis `()`.

```js
setTimeOut(_ => {
  console.log('started timeout')
  // run function
}, 2000)
```

## Double args function

```js
(a,b) => a + b;
```

## Named function

```js
let my_fun = (a,b) => a + b + 10;
```

## Multiline functions require return. E.g

```js
let my_fun = (a,b) => {
  const var_1 = 123;
  const var_2 = 2345;
  return a + b + var_1 + var_2;
}
```
