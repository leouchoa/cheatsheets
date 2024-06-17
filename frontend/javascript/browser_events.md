# Browser Events

List of events available at [MDN](https://developer.mozilla.org/en-US/docs/Web/Events).

Syntax to add/remove a listener:

```js
<event-target>.addEventListener(
    <event-to-listen-for>,
    <function-to-run-when-an-event-happens>,
    useCapture
);

<event-target>.removeEventListener(
    <event-to-listen-for>,
    <function-to-remove>
);
```

## Listening to Events

```html
<!DOCTYPE html>
<html lang="en">
<html>
  <body>
    <div class="container">
      <p>
        <button>Dare to click me?</button>
      </p>
    </div>
    <script src="./main.js"></script>
  </body>
</html>
```

Then `main.js` would be:

```js
document.addEventListener('click', function() {
  // select the element
  const onlybtn = document.querySelector('button');
  // change its background color to red
  onlybtn.style.backgroundColor = 'red';
})
```

## Event Phases

There are three different phases during the lifecycle of an event. They are:

1. the capturing phase
2. the at target phase
3. and the bubbling phase

And they actually follow the order above; first, it's capturing, then at target,
and then the bubbling phase. Most event handlers run during the at target phase,
such as when you attach a click event handler to the button. The event arrives
at the button (its target), and there's only a handler for it right there, so
the event handler gets run.

But sometimes you have a collection of items -- such as a list -- and want to
have one handler cover every item (and still have the option of individual
handlers for some items.) By default, if you click on a child item and a handler
doesn't intercept the click, the event will "bubble" upward to the parent, and
keep bubbling until something handles it or it hits the document.

Capturing, on the other hand, lets the parent intercept an event before it
reaches a child.

In the example bellow the first log message to pop is from `document.body`.
The reason for this is that they're all set happen at the buggling phase (
the `useCapture` arg is set to it's default value of `false`), which means that
the handler:

1. when making it's way down to the last child in the DOM tree, won't
anything. (capturing phase)

2. at the target phase, sees nothing at all.

3. then make it's way back up to the root of the DOM tree, and first sees
the firing of the body handler function trigger (because from bottom up, the
body is first) and finaly the document handler function trigger.

```js
document.addEventListener('click', function () {
   console.log('The document was clicked');
});

document.body.addEventListener('click', function () {
    console.log('The body element was clicked');
});
```

## Event Objects

Adding a parameter to the handler anonymous function allows us to capture
all the rich information about the event:

```js
document.body.addEventListener('click', function (event) {
    console.log('The body element was clicked');
});

```

Then the `event` parameter becomes the event object.
