/* 
设计一个算法，找出数组中最小的k个数。以任意顺序返回这k个数均可。

示例：
输入： arr = [1,3,5,7,2,4,6,8], k = 4
输出： [1,2,3,4]
*/

/**
 * @param {number[]} arr
 * @param {number} k
 * @return {number[]}
 */

// 1.原生API
var smallestK1 = function (arr, k) {
  return arr.sort((a, b) => a - b).slice(0, k);
};

// 2.计数排序
// 将输入的数据转成键存在新的空间
var smallestK2 = function (arr, k) {
  return countingSort(arr, k);
};

let countingSort = (arr, k) => {
  // 将输入的数据转成键存在数组中
  let bucket = [],
    sortedIndex = 0,
    arrLen = arr.length,
    min = Math.min(...arr);
  if (k == 1) {
    return [min];
  }
  if (k == arrLen) {
    return arr;
  }
  for (let i = 0; i < arrLen; i++) {
    // 新开辟的数组空间是用于占位的
    bucket[arr[i] - min] = 1 + (bucket[arr[i] - min] || 0);
  }
  // 按照输入的k的长度输出不为0的元素
  let res = [];
  for (let j = 0; j < bucket.length; j++) {
    while (bucket[j]-- > 0 && sortedIndex < k) {
      res[sortedIndex++] = j + min;
    }
    if (sortedIndex === k) {
      break;
    }
  }
  return res;
};
