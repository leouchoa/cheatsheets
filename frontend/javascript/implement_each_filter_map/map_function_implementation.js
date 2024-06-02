// implement the `map` function that loops in an array or object and calls the given function
// one thing to keep in mind is that we're implementing that in terms of and object  `_` object


const _ = {};

_.map = function(list, callback) {

    let out = [];

    if (Array.isArray(list)) {

        for (let i = 0; i < list.length; i++) {
            out.push(callback(list[i]));
        }
        
        return out;

    } else {

        for (const item in list){
            out.push(callback(list[item]));
        }
        return out;

    }
}

// https://underscorejs.org/ examples

let res_1 = _.map([1, 2, 3], function(num){ return num * 3; });

let res_2 = _.map({one: 1, two: 2, three: 3}, function(num, key){ return num * 3; });

console.log(res_1);

console.log(res_2);

// course example

const weapons = ['candlestick', 'lead pipe', 'revolver'];

const makeBroken = function(item){
  return `broken ${item}`;
};

const brokenWeapons = _.map(weapons, makeBroken);

console.log(brokenWeapons); 