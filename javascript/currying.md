Currying is kinda deconstructing functions arguments to make a new function which is a nested call to it's previous arguments: 

> `f(x,y) = g(x)(y)`

Here's the implementation from [w3docs](https://www.w3docs.com/learn-javascript/currying.html). For the new function to be called notice that we must walk through a chain of individual function calls to finally call the original function.

```
function curry(fn) {
  return function (a) {
    return function (b) {
      return fn(a, b);
    };
  };
} 
```

The classic example is to create the sum function:

```
function sum(a, b) {
  return a + b;
}
let currySum = curry(sum);
console.log(currySum(10)(20)); // 30
```

So we go from `sum(10,20)` to `currySum(10)(20)`. 

But why is it usefull? Well I don't really know. Every example I've found is just not convincing me to use it. But **it is** very usefull to understand how closures work because in the `curry` function implementation, notice that `fn` must have acess to `a` and `b`, otherwise it won't work at all. That's a key closure feature.

**Note:** if you're curious about how to implement curry for an unknown number of arguments, please check out this [w3docs](https://www.w3docs.com/learn-javascript/currying.html) link. The main idea is to combine the spread operator and use the apply function in a recursion style implementation. It's a very smart way to code it.
