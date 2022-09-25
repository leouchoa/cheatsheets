
single args function

```
a => a + 10; \\equivalent to (a) => a + 10;
```

if multiline, need to add a `return`

```
a => {
  const b = 10;
  return a + b;
}
```

void function

```
const x = 100;
() => {
  const a = x*2;
  return a + x;
}
```

double args function

```
(a,b) => a + b;
```

void function

```
() => a + b + 10;
```

named function


```
let my_fun = (a,b) => a + b + 10;
```

multiline functions require return. E.g:
 
```
let my_fun = (a,b) => {
  const var_1 = 123;
  const var_2 = 2345;
  return a + b + var_1 + var_2;
}
```
