This example is inspired by [this](https://frontendmasters.com/courses/js-fundamentals-functional-v2/es5-rewrite-solution/) and [that](https://eloquentjavascript.net/01_values.html#i_pdqDW7Pebo) sources.

The goal is list some one-liners for comparisons and for that we'll use an add function.


```
const add = function(a , b ){ //pre-setting default parameters is also a solution
  /* insert bullet example here */
  console.log(arguments);
  return a + c; 
};
```

- `c = b || 2`: if `b` exists, assign `b` to `c`.
- `c = b && 2`: if `b` exists, assign 2 to `c`.
- `c = true ? b : 2`: the `true` allows us to pick the middle value, `b` in this case.
- `c = false ? 1 : 2`: the `false` allows us to pick the right value, `2` in this case.
