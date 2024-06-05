# Media Queries

Media queries are used to create responsive layouts using breakpoints and while
media queries can be used for a variety of things and in a number of ways,
we are going to focus on what are called breakpoints, which are the viewport
width at which we want our design to change. We then write the code inside that
media query, with a set breakpoint, that we want to go into effect only when
the viewport width that the app is being viewed on is at least the breakpoint
width. Only the CSS that we want to change needs to go here - the original CSS
rules will all still apply, and only the new CSS rules written inside the media
query will override any pre-existing rules.

So the `viewport` is the area of the window in which web content can be seen.
We use the dimensions of the viewport (usually the width, but sometimes the
height) as the basis of our media queries.

Here's an example:

```css
/* alter the body property for width above 900px */
@media(min-width:900px) {
  body{
    font-size: 27px;
    background:red;
  }
}

```

In this case if the viewport width is greater than `900px` the background of the
webpage would turn red and the fontsize would be `27px`.

**Invaluable tip**: when design for mobile, **always** start with the smallest
setting. Which, in code, would translate to putting your `min-width` media
queries at the bottom. For example:

```css
/ *Anything smaller than first breakpoint 600px* /
.container {
  // rules for small screen
}

/ *Medium Screens* /
@media (min-width: 600px) and (max-width:900px) {
  .container {
    // rules for medium-sized screen
  }
}

/ *Large Screens* /
@media (min-width:901px) {
  .container {
    // rules for large screen
  }
}
```

## Resources

- [mdn on media queries](https://developer.mozilla.org/en-US/docs/Web/CSS/Media_Queries/Using_media_queries)
- [mdn on viewports](https://developer.mozilla.org/en-US/docs/Web/CSS/Viewport_concepts#What_is_a_viewport)
- [mdn on using viewports](https://developer.mozilla.org/en-US/docs/Mozilla/Mobile/Viewport_meta_tag)
