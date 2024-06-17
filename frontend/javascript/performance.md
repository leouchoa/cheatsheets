# Performance Tips

- use [`document.Fragment`](https://developer.mozilla.org/en-US/docs/Web/API/DocumentFragment) to manipulate the DOM without going though reflow
and repainting.
  - `Reflow` is the process of the browser laying out the page. It happens when you
  first display the DOM (generally after the DOM and CSS have been loaded),
  and happens again every time something could change the layout. This is a
  fairly expensive (slow) process.
  - `Repaint` happens after reflow as the browser draws the new layout to the
  screen. This is fairly quick, but you still want to limit how often it happens.

For example, if you add a CSS class to an element, the browser often
recalculates the layout of the entire page—that's one reflow and one repaint!

## Resouces

- [google on minimizing browser reflow](https://developers.google.com/speed/articles/reflow)
- [Avoid Large, Complex Layouts and Layout Thrashing](https://developers.google.com/web/fundamentals/performance/rendering/avoid-large-complex-layouts-and-layout-thrashing)
- [Performance analysis reference](https://developers.google.com/web/tools/chrome-devtools/evaluate-performance/reference#rendering)
- [excelent blogpost on reflow and repainting](http://www.stubbornella.org/content/2009/03/27/reflows-repaints-css-performance-making-your-javascript-slow/)

## The JavaScript Event Loop

The simplest explanation of JavaScript's concurrency model uses two rules: If
some JavaScript is running, let it run until it is finished ("run-to-completion"
). If no JavaScript is running, run any pending event handlers.

Since most JavaScript is run in response to an event, this is known as an event
loop: Pick up the next event, run its handler, and repeat.

There are three parts you have to think about around the event loop:

- the Call Stack
- Web APIs/the browser
- an Event Queue

Example:

```js
js console.log('howdy'); // 1
document.addEventListener('click', // 2 
  function numbers() { console.log('123'); }
); 
console.log('ice cream is tasty'); // 3 
```

Steps 1, 2, and 3 are run in order. Step 2 passes an event handler (numbers)
to the browser for future use: the browser will hold this function until there's
a click event.

What happens if someone clicks before this block of code is done?

When there is a click event and there is code already running, the numbers
function can't just be added directly to the Call Stack because of JavaScript's
run-to-completion nature; we can't interrupt any code that might currently be
happening. So the function is placed in the Queue. When all of the functions in
the Call Stack have finished (also known as idle time), then the Queue is checked
to see if anything is waiting. If something is in the Queue, then it's run,
creating an entry on the call stack.

IMPORTANT: The key things to remember here are:

- Current synchronous code runs to completion
- Events are processed when the browser isn't busy. Asynchronous code (such as loading an image) runs outside of this loop and sends an event when it is done.
