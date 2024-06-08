# Destructuring

## Examples

```js
// example 01

const point = [10, 25, -34];
const [x, y, z] = point;

// example 02

let positions = ['Gabrielle', 'Jarrod', 'Kate', 'Fernando', 'Mike', 'Walter'];
let [first, second, third] = positions;

// example 03

const gemstone = {
    type: 'quartz',
    color: 'rose',
    carat: 21.29
};

const {type, color, carat} = gemstone;
```

```js
// selects only the colors
const things = [
      'red',
      'basketball',
      'paperclip',
      'green',
      'computer',
      'earth',
      'udacity',
      'blue',
      'dogs',
];

const [color1, , , color2, , , ,color3] = things;
```

```js
// transform object into array
const favoriteFoods = {
      first: 'pizza',
      second: 'ice cream',
      third: 'tacos',
      fourth: 'sushi',
};

const {first,second, third, fourth} = favoriteFoods;
const foodArray = [first, second, third, fourth];
```

## Destructuring Does Not Preserve Scope

The following code returns `NaN`, because `getArea` cannot access
`this.radius`, as the scope is **not** preserved.

```js
const circle = {
    radius: 10,
    color: 'orange',
    getArea: function() {
        return Math.PI * this.radius * this.radius;
      },
    getCircumference: function() {
        return 2 * Math.PI * this.radius;
      }
};

let {radius, getArea, getCircumference} = circle;
```
