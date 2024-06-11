# Creating Content With JS

Notes taken from: [udacity frontend course](https://www.udacity.com/course/front-end-web-developer-nanodegree--nd0011)

## List of Useful Commands

## Selecting Things

- `document.getElementById`
- `document.querySelector`
- add more here!

## Tips and Tricks

## Updating Content: `textContent` Vs `innerText` vs `innerHTML`

The `textContent` returns all of the `content`, regardless of the css, while
`innerHTML` returns the text as it be seen rendered. This also means that
when updating the content, they behave differently:

```js
// doesn't work as expected, <strong> appears
myElement.textContent = 'The <strong>Greatest</strong> Ice Cream Flavors'; 

// works as expected, Greatest is correclty rendered
myElement.innerHTML = 'The <strong>Greatest</strong> Ice Cream Flavors';
```

- [innerHTML on MDN](https://developer.mozilla.org/en-US/docs/Web/API/Element/innerHTML).
- [textContent on MDN](https://developer.mozilla.org/en-US/docs/Web/API/Node/textContent).
- [innerText on MDN](https://developer.mozilla.org/en-US/docs/Web/API/Node/innerText).

## Creating Content

- `.createElement()`: to create new elements.
- `.creatextNode()`: to add a child element to a parent element as its last child.
- `.appendChild()`: create a text node.
- `.insertAdjacentHTML()`: to put HTML text anywhere around an element.

### `.createElement` creates but doesn't render

This method does create an element, but it **does not** add it to the DOM and
so it wont be rendered on the page. In this case we have to manually add it
to the DOM and one way is to use the `.appendChild()` method:

```js
// create a brand new <span> element
const newSpan = document.createElement('span');

// select the first (main) heading of the page
const mainHeading = document.querySelector('h1');

// **APPEND** (to the bottom of something) the <span> element as the last child
// element of the main heading
mainHeading.appendChild(newSpan);
```

By the way you **can't** call `.appendChild()` on `document`, otherwise you'll
receive an error:

```js
const newSpan = document.createElement('span');

// causes an error
document.appendChild(newSpan);
```

**Attention**:  The `.appendChild()` method will move an element from its
current position to the new position! For Example:

```js
const mainHeading = document.querySelector('h1');
const otherHeading = document.querySelector('h4');
const excitedText = document.createElement('span');

excitedText.textContent = '!!!';
mainHeading.appendChild(excitedText);
// move occurs here! Meaning that `mainHeading` wont have '!!!'
otherHeading.appendChild(excitedText);
```

### `.insertAdjacentHTML()`

By definition, the .appendChild() method will add an element as the last child
of the parent element. It's impossible to put it as the first child or anywhere
else...it has to be the last child.

The `.insertAdjacentHTML()` method is a solution to the "problem". It has to
be called with two arguments:

- the location of the HTML
- the HTML text that is going to be inserted

The first argument to this method will let us insert the new HTML
in one of four different locations:

- `beforebegin` – inserts the HTML text as a previous sibling
- `afterbegin` – inserts the HTML text as the first child
- `beforeend` – inserts the HTML text as the last child
- `afterend` – inserts the HTML text as a following sibling

[Here's a more visual way to explain it:](https://developer.mozilla.org/en-US/docs/Web/API/Element/insertAdjacentHTML#description)

```html
<!-- beforebegin -->
<p>
  <!-- afterbegin -->
  foo
  <!-- beforeend -->
</p>
<!-- afterend -->
```

## Removing Content

Use `.removeChild()`. Example:

```html
<div id="container">
      <p id="extra">This element doesn't need to be here</p>
</div>
```

```js
const someContainer = document.querySelector("#extra");
// attention: the first child may not be the thing you'll want
someContainer.firstChild;
someContainer.firstElementChild;
const firstsome = someContainer.firstElementChild;
someContainer.removeChild(firstsome);
```

But `.removeChild()` requires access to the parent to function.
If you don't want to figure out yourself the parent element:

```js
const mainHeading = document.querySelector('h1');

mainHeading.parentElement.removeChild(mainHeading);
```

Even [easier](https://developer.mozilla.org/en-US/docs/Web/API/ChildNode/remove):

```js
const mainHeading = document.querySelector('h1');

mainHeading.remove();
```

## Modifying Css

To modify one-at-a-time:

```js
const mainHeading = document.querySelector('h1');
mainHeading.style.color = 'red';

```

To modify multiple:

```js
const mainHeading = document.querySelector('h1');
// you the stylesheet EXACTLY as you would with css
mainHeading.style.cssText = 'color: blue; background-color: orange; font-size: 3.5em';
```

**Attention**: by using the `.style.cssText` you're effectively rewriting
the whole property, which that any property set beforehand will be lost!
Example:

```js
<p id="quizzing-quizzes" style="color: orange;">Howdy</p>
const quiz = document.querySelector('#quizzing-quizzes');

// here `color: orange` will be lost!
quiz.style.cssText = 'width: 30px; textDecoration: underline;'
```

### `.setAttribute()`

Another way to set styles for an element is to bypass the `.style.<property>`
and `.style.cssText` properties altogether and use the `.setAttribute()` method:

```js
const mainHeading = document.querySelector('h1');

mainHeading.setAttribute(
  'style',
  'color: blue; background-color: orange; font-size: 3.5em;'
);
```

But whe `setAttribute()` method is not just for styling page elements.
You can use this method to set any attribute for an element:

```js
const mainHeading = document.querySelector('h1');

// add an ID to the heading's sibling element
mainHeading.nextElementSibling.setAttribute('id', 'heading-sibling');

// use the newly added ID to access that element
document.querySelector('#heading-sibling').style.backgroundColor = 'red';

// or more simply
mainHeading.nextElementSibling.style.backgroundColor = 'red';
```

Useful to set an attribute with JavaScript that affects the DOM which then can
be used immediately.

### Change Class Names Using `.classList`

The `.classList` property has a number of methods of its own. Some of the most
popularly used ones are:

- `.add()` - to add a class to the list.
- `.remove()` - to remove a class from the list.
- `.toggle()` - **to add the class if it doesn't exists or remove it from the list,
  if it does already exist**.
- `.contains()` - returns a boolean based on if the class exists in the list or not.

Example:

```html
<h1 id="main-heading" class="ank-student jpk-modal">Learn Web Development at Udacity</h1>
```

```js
const mainHeading = document.querySelector('#main-heading');

// store the list of classes in a variable
const listOfClasses = mainHeading.classList;

// logs out ["ank-student", "jpk-modal"]
console.log(listOfClasses);
```
