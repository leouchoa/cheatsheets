// implement the `map` function that loops in an array or object and calls the given function
// one thing to keep in mind is that we're implementing that in terms of and object  `_` object

const _ = {};

_.filter = function (list,callback) {
    let out = [];

    if (Array.isArray(list)) {

        for (let i = 0; i < list.length; i++) {
            if (callback(list[i])) {
                out.push(list[i]);                
            }
        }
        
        return out;

    } else {

        for (const item in list){
            if (callback(list[item])) {
                out.push(list[i]);                
            }
        }

        return out;

    }

}


// FEM course test

const videoData = [
    {
        name: 'Miss Scarlet',
        present: true,
        rooms: [
            {kitchen: false},
            {ballroom: false},
            {conservatory: false},
            {'dining room': false},
            {'billiard room': false},
            {library: false}
        ]
    },
    {
        name: 'Mrs. White',
        present: false,
        rooms: [
            {kitchen: false},
            {ballroom: false},
            {conservatory: false},
            {'dining room': false},
            {'billiard room': false},
            {library: false}
        ]
    },
    {
        name: 'Reverend Green',
        present: true,
        rooms: [
            {kitchen: false},
            {ballroom: false},
            {conservatory: false},
            {'dining room': false},
            {'billiard room': false},
            {library: false}
        ]
    },
    {
        name: 'Rusty',
        present: false,
        rooms: [
            {kitchen: false},
            {ballroom: false},
            {conservatory: false},
            {'dining room': false},
            {'billiard room': false},
            {library: false}
        ]
    },
    {
        name: 'Colonel Mustard',
        present: true,
        rooms: [
            {kitchen: false},
            {ballroom: false},
            {conservatory: false},
            {'dining room': false},
            {'billiard room': false},
            {library: false}
        ]
    },
    {
        name: 'Professor Plum',
        present: true,
        rooms: [
            {kitchen: false},
            {ballroom: false},
            {conservatory: false},
            {'dining room': false},
            {'billiard room': false},
            {library: false}
        ]
    }
];

let res = _.filter(videoData, function (x) {
    if (!x.present) {
        return x;
    }
});

console.log(res);