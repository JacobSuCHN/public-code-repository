/* 
数字 n 代表生成括号的对数，请你设计一个函数，用于能够生成所有可能的并且 有效的 括号组合。

示例 1：
输入：n = 3
输出：["((()))","(()())","(())()","()(())","()()()"]
示例 2：
输入：n = 1
输出：["()"]
*/

/**
 * @param {number} n
 * @return {string[]}
 */
var generateParenthesis = function (n) {
  const res = [];
  const dfs = (path, left, right) => {
    if (left > n || left < right) return;
    if (left + right === 2 * n) {
      res.push(path);
      return;
    }

    dfs(path + "(", left + 1, right);
    dfs(path + ")", left, right + 1);
  };
  dfs("", 0, 0);
  return res;
};

// 搜索判断 当前这步不对，回到上一步
// 在每次都尝试添加'('/')'
// (前提：有剩余的左括号
// )前提：不能超过已有的左括号
