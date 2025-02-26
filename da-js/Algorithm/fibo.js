function fibo_recursion(n) {
  if (n <= 0) return 0;
  if (n === 1) return 1;
  return fibo_recursion(n - 1) + fibo_recursion(n - 2);
}

function fibo_dp(n) {
  if (n <= 0) return 0;
  if (n <= 1) return 1;
  let arr = [0, 1];
  for (let i = 2; i <= n; i++) {
    arr[i] = arr[i - 1] + arr[i - 2];
  }
  return arr[n];
}

function fibo_dp_optimized(n) {
  if (n <= 0) return 0;
  if (n <= 1) return 1;
  let a = 0;
  let b = 1;
  for (let i = 2; i <= n; i++) {
    b = a + b;
    a = b - a;
  }
  return b;
}
console.log(fibo_recursion(10), fibo_dp(10), fibo_dp_optimized(10));
