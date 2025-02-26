function knapsack_recursion(capacity, objectArr, order) {
  if (order < 0 || capacity <= 0) {
    return 0;
  }
  if (objectArr[order].size > capacity) {
    return knapsack_recursion(capacity, objectArr, order - 1);
  }
  return Math.max(
    objectArr[order].value +
      knapsack_recursion(
        capacity - objectArr[order].size,
        objectArr,
        order - 1
      ),
    knapsack_recursion(capacity, objectArr, order - 1)
  );
}

function knapsack_dp(capacity, objectArr) {
  const n = objectArr.length;
  const f = Array.from({ length: n + 1 }, () => Array(capacity + 1).fill(0));
  for (let i = 1; i <= n; i++) {
    const size = objectArr[i - 1].size;
    const value = objectArr[i - 1].value;
    for (var w = 0; w <= capacity; w++) {
      if (size <= w) {
        f[i][w] = Math.max(f[i - 1][w], f[i - 1][w - size] + value);
      } else {
        f[i][w] = f[i - 1][w];
      }
    }
  }
  return f[n][capacity];
}

function knapsack_dp_optimized(capacity, objectArr) {
  const n = objectArr.length;
  const f = Array(capacity + 1).fill(0);
  for (let i = 0; i < n; i++) {
    const size = objectArr[i].size;
    const value = objectArr[i].value;
    for (let w = capacity; w >= size; w--) {
      f[w] = Math.max(f[w - size] + value, f[w]);
    }
  }
  return f[capacity];
}

function knapsack_greedy(capacity, objectArr) {
  objectArr.sort(function (a, b) {
    return parseFloat(b.value / b.size) - parseFloat(a.value / a.size);
  });
  var n = objectArr.length;
  var selected = 0,
    maxValue = 0;
  for (var i = 0; i < n && selected < capacity; i++) {
    var size = objectArr[i].size,
      value = objectArr[i].value;
    if (size <= capacity - selected) {
      maxValue += value;
      selected += size;
    } else {
      maxValue += value * ((capacity - selected) / size);
      selected = capacity;
    }
  }
  return maxValue;
}
const knapsack1 = [
  { value: 4, size: 3 },
  { value: 5, size: 4 },
  { value: 10, size: 7 },
  { value: 11, size: 8 },
  { value: 13, size: 9 },
];
const knapsack2 = [
  { value: 50, size: 5 },
  { value: 140, size: 20 },
  { value: 60, size: 10 },
  { value: 60, size: 12 },
  { value: 80, size: 20 },
];
console.log(
  knapsack_recursion(30, knapsack1, 4),
  knapsack_dp(30, knapsack1),
  knapsack_dp_optimized(30, knapsack1),
  knapsack_greedy(30, knapsack1)
);
console.log(
  knapsack_recursion(30, knapsack2, 4),
  knapsack_dp(30, knapsack2),
  knapsack_dp_optimized(30, knapsack2),
  knapsack_greedy(30, knapsack2)
);
