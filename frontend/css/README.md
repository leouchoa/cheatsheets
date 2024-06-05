# CSS

## Important Tips

1. At the highest level CSS Grid excels at creating layouts for a webpage, while
Flexbox is a master of content flow for each element that makes up the page layout.

2. When design for mobile, **always** start with the smallest
setting. Which, in code, would translate to putting your `min-width` media
queries at the bottom.

3. On Type Selectors:

- Avoid qualifying ID and class names with type selectors.
- Unless necessary (for example, with helper classes), do not use element
  names in conjunction with IDs or classes. Avoiding unnecessary ancestor
  selectors is useful for performance reasons.
- It is also considered bad practice to use IDs in your CSS files. There are
  no situations where IDs provide a benefit over classes. If you need to use a
  unique name for an element, use a class. (The only benefit IDs provide is
  speed, and is only beneficial on pages with thousands of similar elements.)

## Resources

- [Beginner’s Guide to choosing between CSS Grid and Flexbox](https://medium.com/youstart-labs/beginners-guide-to-choose-between-css-grid-and-flexbox-783005dd2412)
- [udacity frontend course](https://www.udacity.com/course/front-end-web-developer-nanodegree--nd0011)
- [css-trics](https://css-tricks.com/)
- [Css grid visualizer and generator](https://cssgrid-generator.netlify.com/)
- [How items flow into a css grid](https://gedd.ski/post/grid-item-placement/)
- [Using Design Systems for Scalability](https://www.forumone.com/insights/blog/what-is-design-system/)
  - [Udacity Design System](https://veritas.udacity.com/?path=/story/introduction--page)
