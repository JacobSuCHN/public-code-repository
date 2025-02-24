export default function compare(a, b) {
  // 检查是否为相同类型
  if (typeof a !== typeof b) {
    return false;
  }

  // 根据类型进行比较
  switch (typeof a) {
    case 'object':
      // 如果 a 和 b 都是对象且不是 null，则进行深度比较
      if (a === null || b === null) {
        return a === b; // 处理 null 的情况
      }
      return deepCompare(a, b);
    case 'string':
      // 字符串比较
      return a === b;
    case 'number':
    case 'bigint':
    case 'boolean':
      // 数值、BigInt 和布尔值比较
      return a === b;
    case 'array':
      // 数组比较（通过递归调用 compare 进行元素比较）
      return arrayCompare(a, b);
    default:
      // 对于其他类型（如 symbol, function），使用严格相等运算符
      return a === b;
  }
}

// 深度比较两个对象
function deepCompare(obj1, obj2) {
  // 获取对象的键
  const keys1 = Object.keys(obj1);
  const keys2 = Object.keys(obj2);

  // 如果键的数量不同，则对象不同
  if (keys1.length !== keys2.length) {
    return false;
  }

  // 遍历键并进行比较
  for (let key of keys1) {
    if (!keys2.includes(key) || !compare(obj1[key], obj2[key])) {
      return false;
    }
  }

  return true;
}

// 数组比较（通过递归调用 compare 进行元素比较）
function arrayCompare(arr1, arr2) {
  // 如果数组长度不同，则数组不同
  if (arr1.length !== arr2.length) {
    return false;
  }

  // 遍历数组元素并进行比较
  for (let i = 0; i < arr1.length; i++) {
    if (!compare(arr1[i], arr2[i])) {
      return false;
    }
  }

  return true;
}