/* 
给定一个数组 nums，编写一个函数将所有 0 移动到数组的末尾，同时保持非零元素的相对顺序。
请注意 ，必须在不复制数组的情况下原地对数组进行操作。

示例 1:
输入: nums = [0,1,0,3,12]
输出: [1,3,12,0,0]
示例 2:
输入: nums = [0]
输出: [0]
*/
/**
 * @param {number[]} nums
 * @return {void} Do not return anything, modify nums in-place instead.
 */
// 创建指针 指向非0的数字 swap 1.将非0的数字j开始，为0时开始加上非0的数字，最终填写0 nums[j]
var moveZeroes1 = function (nums) {
  let j = 0;
  for (let i = 0; i < nums.length; i++) {
    if (nums[i] !== 0) {
      let temp = nums[j];
      nums[j] = nums[i];
      nums[i] = temp;
      j++;
    }
  }
};

// 遇到数字为0，删除，在末尾+0
var moveZeroes2 = function (nums) {
  let j = 0;
  for (let i = 0; i < nums.length; i++) {
    if (j++ < nums.length) {
      if (nums[i] === 0) {
        nums.splice(i, 1);
        nums.push(0);
        i--; // 序号回到原本的下一个位置
      }
    }
  }
};
