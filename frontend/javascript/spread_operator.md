# Spread Operator

## Simple Example: Concat lists

```js
const fruits = ["apples", "bananas", "pears"];
const vegetables = ["corn", "potatoes", "carrots"];

const produce = [...fruits,...vegetables]

console.log(produce)
```

Also:

```js
const myPackage = ['cheese', 'eggs', 'milk', 'bread'];
console.log(...myPackage);

// output
//
// cheese eggs milk bread

```

## With Objects

```js
let user = {
  name: "Idk",
  age: 11
}

let adminUser = {
  isAdmin: true,
  ...user
}
```

## Better Example

This is example is extracted from [here](https://slides.com/bgando/f2f-final-day-1#/7/14).

Let's take a look at the next function. Notice that accepts 4 parameters and
returns a new data structure from them.

```js
const createTuple = function(a, b, c, d) {
  console.log(arguments);
    //['It', 'be', 'could', 'anyone', 'no one']
  return [[a, c],[ b, d]];
}
```

But what if we call it with 5 parameters instead? It should output an error
right? Well not really... It actually just ignores the last one.

```js
createTuple('It', 'be', 'could', 'anyone', 'no one'); 

// output
//
// Array [ (2) […], (2) […] ]
// 0: Array [ "a", "c" ]
// 1: Array [ "b", "d" ]
// length: 2
// <prototype>: Array []
```

But if you want to also capture the last, because you don't know how many
parameters will given in advance, you can use the spread operator.

```js
const createTuple = function(a, b, c, ...d) {
  console.log(arguments);
  return [[a, c],[ b, d]];
}

createTuple('It', 'be', 'could', 'anyone', 'no one'); 

// output
// 
// [Arguments] {
//   '0': 'It',
//   '1': 'be',
//   '2': 'could',
//   '3': 'anyone',
//   '4': 'no one'
// }
// [ [ 'It', 'could' ], [ 'be', [ 'anyone', 'no one' ] ] ]

```

The spread operator will gather the fourth and beyond arguments passed into an
array so you can capture as many arguments as possible.

A good example, extracted from [here](https://frontendmasters.com/courses/js-fundamentals-functional-v2/passing-arguments-part-2/),
is to pass the spread arguments to functions:

```js
const ifElse = (condition, isTrue, isFalse, ...args) => {
  console.log(args) 
  return condition ? isTrue(...args) : isFalse(...args);
};

const fn1 = () => {console.log("print true!");};
const fn2 = () => {console.log("print false!");};

ifElse(true, fn1, fn2, 'HI', 'BYE', 'Hello');
```
