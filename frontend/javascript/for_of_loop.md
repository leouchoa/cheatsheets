# For ... Of Loop

It's a new iterable interface that allows to customize how objects are iterated,
which loops exclusively over iterable objects - an object that has implemented
the [iterable interface](https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Iteration_protocols).
By default, this includes the data types `String`, `Array`, `Map`, and `Set`
—notably absent from this list is the `Object` data type (i.e. `{}`).
`Objects` are not iterable by default.

```js
// start example
const digits = [0, 1, 2, 3, 4, 5, 6, 7, 8, 9];

// old way
for (let i = 0; i < digits.length; i++) {
    console.log(digits[i]);
};

// the kinda bad way, the for **IN** loop

for (const index in digits) {
      console.log(digits[index]);
};

// the new, sugested way

for (const digit of digits) {
    console.log(digit);
}
```

Benefits of the `for...of loop`:

- You can stop or break a `for...of loop` at anytime.
- You don’t have to worry about adding new properties to objects. The
`for...of loop` will only loop over the values in the object.

## The `forEach()` Loop

The `forEach` loop is another type of for loop in JavaScript. However,
`forEach`() is actually an array method, so it can only be used exclusively
with arrays.
Also it is illegal to break within the `forEach` loop for this reason, but
you can stop the execution of the `forEach` loop by returning from the method
using the return keyword under the conditions that you would want to stop
executing.

## Summary Table

| Family of for loops | `for loop` | `for...in loop` | `forEach()` | `for...of loop` |
|---------------------|------------|-----------------|-------------|-----------------|
| **Benefits**        | - Common  - Good for arrays | - Eliminates the need to keep track of a counter and exit condition  - Eliminates the use of an index | - Eliminates the need to keep track of a counter and exit condition  - Eliminates the use of an index | - Loops over any data that is iterable (as opposed to enumerable)  - Eliminates use of an index  - Can stop or break anytime |
| **Drawbacks**       | - Keeping track of the counter and exit condition  - Possible confusion  - Not as easy to use if data not structured like an array | - Still uses an index to access the values in an array  - Possible confusion  - Loop over all enumerable properties - including functions | - Only works with arrays  - Unable to break - must return | - Don't have access to an index, which is sometimes needed |
