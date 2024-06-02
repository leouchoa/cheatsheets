// implement the `each` function that loops in an array or object and calls the given function
// one thing to keep in mind is that we're implementing that in terms of and object  `_` object

const _ = {};

_.each = function(list, callback) {    
    for (const i in list) {
        callback(list[i]);        
    }
 }


 _.newEach = function(list, callback) {    

    if (Array.isArray(list)) {
        for (let i = 0; i < list.length; i++) {
            callback(list[i]);
        }
    } else {
        for (const item in list){
            callback(item);
        }
    }
 }


var logger = function(val){
    console.log(val);
};

var rooms_arr = ['observatory','ballroom', 'library'];

_.each(rooms_arr,logger);

var rooms_obj = {a:'ad',b:'bq',c:'cw'};

_.each(rooms_obj,logger);
