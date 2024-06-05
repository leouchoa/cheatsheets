# Colors

Colors in CSS can be specified by the following methods:

- Hexadecimal colors
- RGB colors
- Predefined/Cross-browser color names
- RGBA colors
- HSL colors
- HSLA colors

## Hexadecimal Colors

A hexadecimal color is specified with: #RRGGBB, where the RR (red), GG (green)
and BB (blue) hexadecimal integers specify the components of the color. All
values must be between 00 and FF.

For example, the #0000ff value is rendered as blue, because the blue component
is set to its highest value (ff) and the others are set to 00.
Example on how to define different HEX colors:

```css
#p1 {
  background-color: #ff0000;
}

#p2 {
  background-color: #00ff00;
}

#p3 {
  background-color: #0000ff;
}
```

## RGB Colors

An RGB color value is specified with the `rgb()` function:

```css
rgb(red, green, blue)
```

Each parameter (red, green, and blue) defines the intensity of the color and can
be an integer between 0 and 255 or a percentage value (from 0% to 100%). For
example, the `rgb(0,0,255)` value is rendered as blue, because the blue parameter
is set to its highest value (255) and the others are set to 0.

Also, the following values define equal color: `rgb(0,0,255)` and `rgb(0%,0%,100%)`.
Example:

```css
#p1 {
  background-color: rgb(255, 0, 0);
}

#p2 {
  background-color: rgb(0, 255, 0);
}

#p3 {
  background-color: rgb(0, 0, 255);
}
```

## Predefined/Cross-browser Color Names

140 color names are predefined in the HTML and CSS color specification. There's
quite a few of these - check out this [list](https://developer.mozilla.org/en-US/docs/Web/CSS/color_value).
