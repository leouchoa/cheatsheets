const doubleOdd = (arr) =>
  arr.map((num) => {
    if (num % 2 !== 0) {
      return num * 2;
    } else return num;
  });

testSets = [
  [
    [2, 6],
    [2, 6],
  ],
  [
    [2, 3, 3, 5, 7, 10],
    [2, 6, 6, 10, 14, 10],
  ],
  [
    [7, 1432, 12, 13, 107],
    [14, 1432, 12, 26, 214],
    [[], []],
  ],
];

function codeTest(testSets) {
  for (const test of testSets) {
    const doubleArr = doubleOdd(test[0]);
    for (let i = 0; i <= doubleArr.length; i++)
      if (doubleArr[i] != test[1][i]) {
        return "Your code fails. Try again!";
      }
  }
  return "Your code passes!";
}

console.log(codeTest(testSets));
