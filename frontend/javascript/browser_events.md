# Browser Events

List of events available at [MDN](https://developer.mozilla.org/en-US/docs/Web/Events).

## Listening to Events

```html
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>My Webpage</title>
    <!-- Link to your CSS file -->
    <link rel="stylesheet" href="styles.css">
</head>
<body>
    <header>
        <h1>Welcome to My Webpage</h1>
    </header>

    <main>
        <section class="card">
            <div class="card__content">This is the card content.</div>
        </section>
    </main>

    <footer>
        <p>2024 My Webpage</p>
    </footer>

    <!-- This is where you add the js script!! file -->
    <!-- Link to your JavaScript file -->
    <script src="main.js"></script>
</body>
</html>

```

Then `main.js` would be:

```js
document.addEventListener('click', function() {
  // select the element
  const mainHeading = document.querySelector('h1');
  // change its background color to red
  mainHeading.style.backgroundColor = 'red';
})
```
