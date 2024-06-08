# Object literal shorthand

DRY.

```js
// example start
let type = 'quartz';
let color = 'rose';
let carat = 21.29;

// instead of using this:
const gemstone = {
    type: type,
    color: color,
    carat: carat
};

// use this:
const gemstone = { type, color, carat, };
```

## Shorthand method names

When writing function inside objects, you don't need to use the
`function` keyword:

```js
// example start
let type = 'quartz';
let color = 'rose';
let carat = 21.29;

// instead of using this:
const gemstone = {
  type,
  color,
  carat,
  calculateWorth: function() {
    ...
  }
};

// use this:
let gemstone = {
    type,
    color,
    carat,
    calculateWorth() { ... }
};
}
```
