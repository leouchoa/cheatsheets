# Display and Positioning: Z-index

When elements overlap, they are ordered on the z-axis
(i.e., which element covers another). The z-index CSS property can be used to
specify the z-order of these overlapping elements. Overlapping elements with a
larger z-index cover those with a smaller one.

Elements may overlap for a number of reasons; for instance, elements positioned
absolutely, or elements with negative values set for their margin property.
In these instances we need a way to determine which element should be displayed
on top. Without explicitly using z-index the last element written to the DOM
(the last element you wrote in your code) will appear on top of all the others,
and so on up the chain of your elements.

As an example, let’s say we had two rectangles, positioned absolutely and
overlapping each other-- the code for that could look like this:

```css
<style>
.box {
  width: 200px;
   height: 200px;
  position: absolute;
}
```

```css
# one {
  background: red;
  top: 100px;
  left: 150px;
}
```

```css
# two {
  background: yellow;
  top: 80px;
  left: 100px;
}
```

```html
</style>

<html>
  <div id=”one” class =”box”> Box One </div>
  <div id=”two” class =”box”> Box Two </div>
</html>
```

By default, the element with the id two would be displayed on top because it
comes after element one in the code. However, if we wanted to display the first
element on top we could use z-index, by giving each of the elements a numeric
value for z-index and making sure that the value for element one is higher.
The updated CSS could look like this:

```css

# one {

  background: red;
  top: 100px;
  left: 150px;
  z-index:1;
}
```

```css


# two {

  background: yellow;
  top: 80px;
  left: 100px;
  z-index: -1;
}
```

Notice that element one has been given a z-index value of 1, and element two
has been given a z-index value of -1. If more elements were involved we could
use a wider range of values and the same rules would apply-- so that an element
with z-index 100 would be displayed above an element with a z-index value of 99,
and below.

## Resources

- [udacity frontend course](https://www.udacity.com/course/front-end-web-developer-nanodegree--nd0011)
