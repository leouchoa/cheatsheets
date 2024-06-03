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

## Underlined Text

The text-decoration property determines whether text is underlined or not. By
setting it to none, we can remove the default underline from all of our links.
We’ll discuss link styles in-depth later on.

```css
a {
  text-decoration: none;
}
```

## Strikethrough Text

The other common value for text-decoration is line-through to strike out “deleted”
text. But, remember that meaning should always be conveyed through HTML—not CSS.
It’s better to use the `<ins>` and `<del>` elements instead of adding a line-through
style to, say, an ordinary `<p>` element.

## Line Height

The following properties describe a bit about space between text:

- margin-top (or padding-top)
- margin-bottom (or padding-bottom)
- line-height

The first two they define the vertical space between separate paragraphs. The
new line-height property determines the amount of space between lines in the
same paragraph.

In traditional typography, line-height is called “leading” because printers
used little strips of lead to increase the space between lines of text.
