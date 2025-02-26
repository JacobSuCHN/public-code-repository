const bubbleSort = (arr) => {
  const length = arr.length;
  if (length <= 1) return;
  for (let i = 0; i < length - 1; i++) {
    for (let j = 0; j < length - i - 1; j++) {
      if (arr[j] > arr[j + 1]) {
        const t = arr[j];
        arr[j] = arr[j + 1];
        arr[j + 1] = t;
      }
    }
  }
  return arr;
};

const arr1 = [7, 8, 4, 5, 6, 3, 2, 1];
console.time("bubble sort time");
console.log("sorted arr", bubbleSort(arr1));
console.timeEnd("bubble sort time");

const bubbleSortOptimized = (arr) => {
  const length = arr.length;
  if (length <= 1) return;
  for (let i = 0; i < length - 1; i++) {
    let hasChange = false;
    for (let j = 0; j < length - i - 1; j++) {
      if (arr[j] > arr[j + 1]) {
        const t = arr[j];
        arr[j] = arr[j + 1];
        arr[j + 1] = t;
        hasChange = true;
      }
    }
    if (!hasChange) break;
  }
  return arr;
};

const arr2 = [7, 8, 4, 5, 6, 3, 2, 1];
console.time("bubble sort time(optimized)");
console.log("sorted arr", bubbleSortOptimized(arr2));
console.timeEnd("bubble sort time(optimized)");

const insertionSort = (arr) => {
  const length = arr.length;
  if (length <= 1) return;
  let preIndex, current;
  for (let i = 1; i < length; i++) {
    preIndex = i - 1;
    current = arr[i];

    while (preIndex >= 0 && arr[preIndex] > current) {
      arr[preIndex + 1] = arr[preIndex];
      preIndex--;
    }
    if (preIndex + 1 != i) {
      arr[preIndex + 1] = current;
    }
  }
  return arr;
};

const arr3 = [7, 8, 4, 5, 6, 3, 2, 1];
console.time("insertion sort time");
console.log("sorted arr", insertionSort(arr3));
console.timeEnd("insertion sort time");

const binaryInsertionSort = (arr) => {
  const length = arr.length;
  if (length <= 1) return;

  let current, i, j, low, high, middle;
  for (i = 1; i < length; i++) {
    low = 0;
    high = i - 1;
    current = arr[i];
    while (low <= high) {
      middle = (low + high) >> 1; // x>>1 <=> Math.floor(x/2)
      if (arr[i] >= arr[middle]) {
        low = middle + 1;
      } else {
        high = middle - 1;
      }
    }
    for (j = i; j > low; j--) {
      arr[j] = arr[j - 1];
    }
    arr[low] = current;
  }
  return arr;
};

const arr4 = [7, 8, 4, 5, 6, 3, 2, 1];
console.time("binary insertion sort time");
console.log("sorted arr", binaryInsertionSort(arr4));
console.timeEnd("binary insertion sort time");

const selectionSort = (arr) => {
  const length = arr.length;
  if (length <= 1) return;
  let minIndex;
  for (let i = 0; i < length; i++) {
    minIndex = i;
    for (let j = i; j < length; j++) {
      if (arr[j] < arr[minIndex]) {
        minIndex = j;
      }
    }
    const t = arr[i];
    arr[i] = arr[minIndex];
    arr[minIndex] = t;
  }
  return arr;
};

const arr5 = [7, 8, 4, 5, 6, 3, 2, 1];
console.time("selection sort time");
console.log("sorted arr", selectionSort(arr5));
console.timeEnd("selection sort time");

const mergeSort = (arr) => {
  const length = arr.length;
  if (length < 2) return arr;
  let middle = Math.floor(length / 2);
  let left = arr.slice(0, middle);
  let right = arr.slice(middle);

  return merge(mergeSort(left), mergeSort(right));
};
const merge = (left, right) => {
  const result = [];
  while (left.length && right.length) {
    if (left[0] <= right[0]) {
      result.push(left.shift());
    } else {
      result.push(right.shift());
    }
  }
  while (left.length) result.push(left.shift());
  while (right.length) result.push(right.shift());

  return result;
};

const arr6 = [7, 8, 4, 5, 6, 3, 2, 1];
console.time("merge sort time");
console.log("sorted arr", mergeSort(arr6));
console.timeEnd("merge sort time");

const quickSort = (arr) => {
  const length = arr.length;
  if (length < 2) return arr;
  const midIndex = Math.floor(length / 2);
  const valArr = arr.splice(midIndex, 1);
  const left = [];
  const right = [];
  const midIndexVal = valArr[0];
  for (let i = 0; i < arr.length; i++) {
    if (arr[i] < midIndexVal) {
      left.push(arr[i]);
    } else {
      right.push(arr[i]);
    }
  }

  return quickSort(left).concat(midIndexVal, quickSort(right));
};

const arr7 = [7, 8, 4, 5, 6, 3, 2, 1];
console.time("quick sort time");
console.log("sorted arr", quickSort(arr7));
console.timeEnd("quick sort time");
