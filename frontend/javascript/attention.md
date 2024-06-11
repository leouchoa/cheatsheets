# Attenton Points

## Listen To The Right Event

Consider the following two codes:

```js
const mainHeading = document.querySelector("h1");
mainHeading.addEventListener("mouseover", function () {
    // mainHeading.style.backgroundColor = "red";
    mainHeading.textContent = "Build an AR App";
});
mainHeading.addEventListener("mouseout", function () {
    // mainHeading.style.backgroundColor = "red";
    mainHeading.textContent = "Learn ARKit";
});
```

```js
const mainHeading = document.querySelector("h1");
document.addEventListener("mouseover", function () {
      // mainHeading.style.backgroundColor = "red";
      mainHeading.textContent = "Build an AR App";
});
document.addEventListener("mouseout", function () {
      // mainHeading.style.backgroundColor = "red";
      mainHeading.textContent = "Learn ARKit";
});
```

The first works perfectly, the second works really bad, although both of them
try to do the same thing. The difference between those two is that the first
listens to `h1` events, while the second listens to `document` events.
The difference is huge, so choose your target wisely!
