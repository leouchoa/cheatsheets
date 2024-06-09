# The Rest Parameter

It's kinda the opposite of the spread operator. Example:

```js
printPackageContents('cheese', 'eggs', 'milk', 'bread');
function printPackageContents(...items) {
   for(const item of items) {
       console.log(item);
     }
}
```

An use case for the rest parameter is when you’re working with variadic
functions, which are are functions that take an indefinite number of arguments,
like the `sum` function example bellow:

```js

function sum(...nums) {
    let total = 0;  
    for(const num of nums) {
        total += num;
      }
  return total;
}
```

or the example bellow:

```js
function average(...nums) {
  let sum = 0;
  for(const num of nums) {
    sum+=num;
  }
  // note the `nums.length`, you don't need to keep track of 
  // the total of items
  if (nums.length > 0) return sum/nums.length;
  else return sum;
}
```
