# Flexbox

The Flexbox model relies on two axes: the main axis and the cross axis. The
main axis is defined by flex-direction, which has four possible values:

- row
- row-reverse
- column
- column-reverse

The two row settings will create the main axis horizontally - or inline
direction. The two column settings will create the main axis vertically - or
block direction. block or inline here refer to the CSS display settings which
we have covered previously.

If you set

```css
.container{
  display:flex;
  flex-direction: row
}
```

you're telling css that the main axis will be the row and secondary will be
the column.

## Ordering Elements With Flexbox

There are three ways to explicitly set the order in which items will appear
in a grid:

- Moving the HTML code for the elements themselves to reorder
- Appending `-reverse` to `row` or `column` will reverse the order in the
specified row or column
- Using the `order` property of the individual items inside the grid

## Aligning Elements

To align items on the cross axis use align-items with the possible values:

- stretch
- flex-start
- flex-end
- center

To justify content on the main axis use justify-content, which has the possible values:

- flex-start
- flex-end
- center
- space-around
- space-between
- space-evenly
