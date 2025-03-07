/* 
给你一个长度为 n 的整数数组 nums 和 一个目标值 target。请你从 nums 中选出三个整数，使它们的和与 target 最接近。
返回这三个数的和。
假定每组输入只存在恰好一个解。

示例 1：
输入：nums = [-1,2,1,-4], target = 1
输出：2
解释：与 target 最接近的和是 2 (-1 + 2 + 1 = 2)。
示例 2：
输入：nums = [0,0,0], target = 1
输出：0
解释：与 target 最接近的和是 0（0 + 0 + 0 = 0）。
*/

/**
 * @param {number[]} nums
 * @param {number} target
 * @return {number}
 */
var threeSumClosest = function (nums, target) {
  let n = nums.length;
  if (n === 3) {
    return getSum(nums);
  }
  // 1.从小到大排序
  nums.sort((a, b) => a - b);

  let min = Infinity; // 最接近的插值
  let res; // 三数之和
  // 2.找到一个基础的指针，并且至少要保留出两个位置，确保是3个数字
  for (let i = 0; i < nums.length - 2; i++) {
    let basic = nums[i];
    let left = i + 1; // 左指针在basic的右边第一位
    let right = n - 1; // 右指针为当前的最后一项

    while (left < right) {
      let sum = basic + nums[left] + nums[right];
      let diff = Math.abs(sum - target);
      if (diff < min) {
        min = diff;
        res = sum;
      }
      if (sum < target) {
        left++;
      } else if (sum > target) {
        right--;
      } else {
        return sum;
      }
    }
  }
  return res;
};
function getSum(nums) {
  return nums.reduce((total, current) => total + current, 0);
}

// 排序+双指针

// target Math.abs()

// a b+c target-a

// a Pb Pc a+b+c>=target c左移 a+b+c<target b右移
