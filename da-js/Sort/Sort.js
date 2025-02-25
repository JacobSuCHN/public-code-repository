const bubbleSort = (arr) => {
  console.time("bubble sort time");
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
  console.log("sorted arr", arr);
  console.timeEnd("bubble sort time");
  return arr;
};

// const arr1 = [7, 8, 4, 5, 6, 3, 2, 1];
// bubbleSort(arr1);

const bubbleSortOptimized = (arr) => {
  console.time("bubble sort time(optimized)");
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
  console.log("sorted arr", arr);
  console.timeEnd("bubble sort time(optimized)");
  return arr;
};

// const arr2 = [7, 8, 4, 5, 6, 3, 2, 1];
// bubbleSortOptimized(arr2);

const insertionSort = (arr) => {
  console.time("insertion sort time");
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
  console.log("sorted arr", arr);
  console.timeEnd("insertion sort time");
  return arr;
};
// const arr3 = [7, 8, 4, 5, 6, 3, 2, 1];
// insertionSort(arr3);

const binaryInsertionSort = (arr) => {
  console.time("binary insertion sort time");
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
  console.log("sorted arr", arr);
  console.timeEnd("binary insertion sort time");
  return arr;
};
// const arr4 = [7, 8, 4, 5, 6, 3, 2, 1];
// binaryInsertionSort(arr4);

const selectionSort = (arr) => {
  console.time("selection sort time");
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
  console.log("sorted arr", arr);
  console.timeEnd("selection sort time");
  return arr;
};

// const arr5 = [7, 8, 4, 5, 6, 3, 2, 1];
// selectionSort(arr5);
