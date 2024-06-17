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

## To Remove a Listener, It Has To Be The Same Added

The following code works as expected:

```js
function myEventListeningFunction() {
        console.log('howdy');
}

// adds a listener for clicks, to run the `myEventListeningFunction` function
document.addEventListener('click', myEventListeningFunction);

// immediately removes the click listener that should run the 
// `myEventListeningFunction` function
document.removeEventListener('click', myEventListeningFunction);
}
```

This one does not:

```js
// adds a listener for clicks, to run the `myEventListeningFunction` function
document.addEventListener('click', function myEventListeningFunction() {
        console.log('howdy');
});

// immediately removes the click listener that should run the 
// `myEventListeningFunction` function
document.removeEventListener('click', function myEventListeningFunction() {
        console.log('howdy');
});
```

The reason is that in the first case the listener is the same, they're pointing
to the same thing (same memory addresses). The second doesn't work listeners
are different (different memory addresses).

## Care Not To Add Too Many Events

In the following code we create 200 `p` tags, 200 event listeners with
200 different listeners handle functions. That's not so good.

```js
const myCustomDiv = document.createElement('div');

for (let i = 1; i <= 200; i++) {
    const newElement = document.createElement('p');
    newElement.textContent = 'This is paragraph number ' + i;

    newElement.addEventListener('click', function respondToTheClick(evt) {
        console.log('A paragraph was clicked.');
    });

    myCustomDiv.appendChild(newElement);
}

document.body.appendChild(myCustomDiv);
```

The following code, on the other hand, creates only a single handle
function and a single event listener to all 200 new `p` tags. That's way
better, care not to add unnecessary things.

```js
const myCustomDiv = document.createElement('div');

function respondToTheClick() {
    console.log('A paragraph was clicked.');
}

for (let i = 1; i <= 200; i++) {
    const newElement = document.createElement('p');
    newElement.textContent = 'This is paragraph number ' + i;

    myCustomDiv.appendChild(newElement);
}

myCustomDiv.addEventListener('click', respondToTheClick);

document.body.appendChild(myCustomDiv);
```

## Why Wont the Following Run?

```js
const numbers = [5,1,4,3,2];
for ( var i = 0; i < numbers.length; i++) {
    setTimeout(()=>  console.log(`This is message ${numbers[i]}`), numbers[i] * 100);
} 
```

The code that executes in a setTimeout function uses the current value of any
variables, not the value at the time of the setTimeout call.

Loops in JavaScript run quickly so the code in the setTimeout function doesn't
run until after the loop is finished. That means when it evaluates number[i], it
uses the current value of i, which, at the end of the loop, is 5. There are only
5 elements in the numbers array so the value of numbers[5] is undefined.

We can fix this by using let instead of var. let creates a new lexical scope for
each setTimeout call so the value of i in that call remains fixed at the value of
i when the call was made.

```js
for ( let i = 0; i < numbers.length; i++) {
    setTimeout(()=>  console.log(`This is message ${numbers[i]}`), numbers[i] * 100);
} 
```
