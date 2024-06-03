# Tips and Tricks

Wanna see every single "box" that makes up a page?
Try putting this in the stylesheet temporarily:

```css
* {
  border: 1px solid red !important;
}
```

## Fontsize `px` vs `em`

The `px` (pixel) and `em`. The former is what you would intuitively call a
pixel, regardless of whether the user has a retina display or not, and the
latter is the current font size of the element in question.

The em unit is very useful for defining sizes relative to some base font.
For example, if you set the font-size of body to 16px, you could then set other
element’s font-size value relative to that 16px. Here’s what that could look like:

```css

body {
 font-size: 16px;
}

# one {
  font-size: 1.5em
}

# two {
  font-size: 0.5em
}
```

In this example, one would have font bigger than 16px, and two would have font
smaller than 16px.
