# What is projecting

Projecting is extracting values of a data structure and creating another data structure.

To explain it better, here goes an example based an [exercise](https://slides.com/bgando/f2f-final-day-1#/7/10) of the [Fundamentals to Functional Day 1 v2](https://frontendmasters.com/courses/js-fundamentals-functional-v2/projecting-exercise/). 

To setup the exercise please go to [underscorejs.org](underscorejs.org), open up your developer tools and go to the console. Then copy the content of [this link](http://jsbin.com/duvafoc/edit?html,js,output) and paste into the console.

In this example the goal is to create an **array** with names associated with `present: true`. 
We can do this with [arrow functions](https://github.com/leouchoa/js_cheatsheet/blob/main/arrow_funs.md). First we `filter` the objects associated with `present: true` and then we extract the names using the `map` function.

```
aux = _.filter(videoData, (x) => x.present); //filtering the present characters
res = _.map(res1, x => x.name); //using map to extract the names
console.log(res);
```
The output should be an array that looks like this:

```
Array(4) [ "Miss Scarlet", "Reverend Green", "Colonel Mustard", "Professor Plum" ]
0: "Miss Scarlet"
1: "Reverend Green"
2: "Colonel Mustard"
3: "Professor Plum"
length: 4
```

