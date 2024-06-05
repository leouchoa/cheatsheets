# Grid

- [css-tricks guide to css `grid`](https://css-tricks.com/snippets/css/complete-guide-grid/)

CSS Grid v. Flexbox

- Grid is two dimensional, while Flex is one
- Grid is layout first, while Flexbox is content first
- Flex is for components of an app, Grid is for the app layout itself

CSS Grid does not replace Flexbox. Each can achieve things that the other is not
capable of, and in fact, a true master can use Flexbox and CSS Grid together in
harmony to create the ultimate webpage layout.

At the highest level CSS Grid excels at creating layouts for a webpage, while
Flexbox is a master of content flow for each element that makes up the page layout.

## Columns and Rows

After setting the display property of your container `div` to `grid`, the next step
is to set the rows and columns in your grid which can be done with the CSS properties:

- `grid-template-columns`
- `grid-template-rows`

And to define gutters between rows and columns you can use the property
`grid-gap` on the parent container that has the display property set to `grid`.

## Grid Areas

The `grid-area` property specifies a particular area or set of rows and columns
that a grid item occupies. It is applied to the grid item itself with CSS.
Here is an example:

```css
.item{
  / *row start/column start/ row end/ column end* /
  grid-area: 1/2/3/3
}
```

Because grid-area is shorthand for the properties: `grid-row-start`,
`grid-column-start`, `grid-row-end` and `grid-column-end`, the code above places
the item from rows 1-3, and columns 2-3.

Another example:

By applying the css rule `grid-area: 2 / 1 / 2 / 4`, we'll have a placement
of row 2 and columns 1-3, because the row starts and ends with 2 and the
column starts with 1 and ends with 4.

### Naming Grid Areas

```css
.container {
  display:grid;
  grid-template-columns: 300px 300px 300px;
  grid-template-rows: 250px 600px;
  grid-template-areas: 
    "hd hd hd hd hd hd hd hd"
    "sd sd sd main main main main main"
    "ft ft ft ft ft ft ft ft";
}
```

The named areas in the grid are then assigned to each element according to
where you want them to be displayed in the grid:

```css
.header {
  grid-area: hd;
}
```

In the example above the element with the class header will stretch across the
entire first row of columns because we have assigned it the `grid-area` `hd`, and
we have defined the area `hd` with the value for `grid-template-areas` in the
parent element.

## Some Advanced Capabilities

CSS Grid includes advanced capabilities for creating large and complex grids.
Some of these are:

- The `fr` unit, that represents a fraction of the available space in the grid
container.
- Track listings with `repeat()` notation
  - For example, this `grid-template-columns: 1fr 1fr 1fr 1fr 1fr 1fr 1fr;` can
  be replaced by `grid-template-columns: repeat(7, 1fr);`.
- Track sizing and `minmax()`.
  - For example, the `grid-auto-rows` property can be used to generate the
  number of rows based on the content and available space. So using
  `grid-auto-rows: minmax(100px, auto);` would create rows that are at least
  100px tall and can be as tall as the content inside them demands.
