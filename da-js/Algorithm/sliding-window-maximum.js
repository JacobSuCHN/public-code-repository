/* 
给你一个整数数组 nums，有一个大小为 k 的滑动窗口从数组的最左侧移动到数组的最右侧。你只可以看到在滑动窗口内的 k 个数字。滑动窗口每次只向右移动一位。
返回 滑动窗口中的最大值 。

示例 1：
输入：nums = [1,3,-1,-3,5,3,6,7], k = 3
输出：[3,3,5,5,6,7]
解释：
滑动窗口的位置                最大值
---------------               -----
[1  3  -1] -3  5  3  6  7       3
 1 [3  -1  -3] 5  3  6  7       3
 1  3 [-1  -3  5] 3  6  7       5
 1  3  -1 [-3  5  3] 6  7       5
 1  3  -1  -3 [5  3  6] 7       6
 1  3  -1  -3  5 [3  6  7]      7
示例 2：
输入：nums = [1], k = 1
输出：[1]
*/

/**
 * @param {number[]} nums
 * @param {number} k
 * @return {number[]}
 */
var maxSlidingWindow = function (nums, k) {
  let window = new MonotionQueue();
  let res = [];
  for (let i = 0; i < nums.length; i++) {
    if (i < k - 1) {
      // 此时要做的是先把窗口的前k-1的元素加进去
      window.push(nums[i]);
    } else {
      window.push(nums[i]);
      res.push(window.max());
      // 移除最后的元素
      window.pop(nums[i - (k - 1)]);
    }
  }
  return res;
};
const MonotionQueue = function () {
  let queue = [];
  // 在队尾添加元素
  this.push = function (n) {
    // 把之前不符合单调性的元素删除（小于自己的元素）
    while (queue.length && queue[queue.length - 1] < n) {
      queue.pop();
    }
    queue.push(n);
  };
  //
  this.pop = function (n) {
    if (n === queue[0]) {
      // 当n是最开始的头部元素
      queue.shift();
    }
  };
  // 返回队列的最大值
  this.max = function () {
    return queue[0];
  };
};
