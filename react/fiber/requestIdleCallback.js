const ImmediatePriority = 1; // 立即执行的优先级, 级别最高 [点击事件 输入框]
const UserBlockingPriority = 2; // 用户阻塞级别的优先级, [滚动 拖拽这些]
const NormalPriority = 3; // 正常的优先级 [redner 列表 动画 网络请求]
const LowPriority = 4; // 低优先级  [分析统计]
const IdlePriority = 5; // 最低阶的优先级, 可以被闲置的那种 [console.log]

// 获取当前时间
function getCurrentTime() {
  // 使用 performance.now() 获取高精度的时间戳
  return performance.now();
}

class SimpleScheduler {
  constructor() {
    /**
     * @type {Array<{callback: function, priorityLevel: number, expirationTime: number}>}
     * 任务队列，存储待执行的任务
     * 每个任务包含回调函数、优先级和过期时间
     * 优先级越高，过期时间越短
     * 过期时间是当前时间加上超时时间
     * 超时时间根据优先级不同而不同
     */
    this.taskQueue = [];
    /**
     * @type {boolean}
     * 是否正在执行任务
     * 用于避免重复调度
     */
    this.isPerformingWork = false;

    // 使用 MessageChannel 处理任务调度
    const channel = new MessageChannel();
    // channel.port1 用于接收消息，port2 用于发送消息
    this.port = channel.port2;
    // 监听 port1 的消息事件，当有消息时执行 performWorkUntilDeadline
    channel.port1.onmessage = this.performWorkUntilDeadline.bind(this);
  }

  // 调度任务
  /**
   * @param {number} priorityLevel - 任务的优先级
   * @param {function} callback - 任务回调函数
   */
  scheduleCallback(priorityLevel, callback) {
    const curTime = getCurrentTime();
    let timeout;
    // 根据优先级设置超时时间
    switch (priorityLevel) {
      case ImmediatePriority:
        timeout = -1;
        break;
      case UserBlockingPriority:
        timeout = 250;
        break;
      case LowPriority:
        timeout = 10000;
        break;
      case IdlePriority:
        timeout = 1073741823;
        break;
      case NormalPriority:
      default:
        timeout = 5000;
        break;
    }

    const task = {
      callback,
      priorityLevel,
      expirationTime: curTime + timeout, // 直接根据当前时间加上超时时间
    };

    this.push(this.taskQueue, task); // 将任务加入队列
    // 如果当前没有正在执行的任务，则调度执行
    this.schedulePerformWorkUntilDeadline();
  }

  /**
   * 调度执行任务直到截止时间
   */
  schedulePerformWorkUntilDeadline() {
    if (!this.isPerformingWork) {
      this.isPerformingWork = true;
      this.port.postMessage(null); // 触发 MessageChannel 调度
    }
  }

  /**
   * 执行任务直到截止时间
   */
  performWorkUntilDeadline() {
    this.isPerformingWork = true;
    this.workLoop();
    this.isPerformingWork = false;
  }

  /**
   * 工作循环
   * 遍历任务队列，执行每个任务的回调函数
   * 如果任务队列为空，则结束循环
   * 如果有任务被执行，则继续循环，直到没有更多任务
   * 任务执行完毕后，清空已完成的任务
   * 该方法会在 performWorkUntilDeadline 中被调用
   */
  workLoop() {
    let curTask = this.peek(this.taskQueue);
    while (curTask) {
      const callback = curTask.callback;
      if (typeof callback === "function") {
        callback(); // 执行任务
      }
      this.pop(this.taskQueue); // 移除已完成任务
      curTask = this.peek(this.taskQueue); // 获取下一个任务
    }
  }

  // 以下未模拟，React源码并不是直接使用这些方法，而是通过调度器来管理任务的执行
  // 获取队列中的任务
  peek(queue) {
    return queue[0] || null;
  }

  // 向队列中添加任务
  push(queue, task) {
    queue.push(task);
    queue.sort((a, b) => a.expirationTime - b.expirationTime); // 根据优先级排序，优先级高的在前 从小到大
  }

  // 从队列中移除任务
  pop(queue) {
    return queue.shift();
  }
}

// 测试
const scheduler = new SimpleScheduler();

scheduler.scheduleCallback(LowPriority, () => {
  console.log("Task 1: Low Priority");
});

scheduler.scheduleCallback(ImmediatePriority, () => {
  console.log("Task 2: Immediate Priority");
});

scheduler.scheduleCallback(IdlePriority, () => {
  console.log("Task 3: Idle Priority");
});

scheduler.scheduleCallback(UserBlockingPriority, () => {
  console.log("Task 4: User Blocking Priority");
});

scheduler.scheduleCallback(NormalPriority, () => {
  console.log("Task 5: Normal Priority");
});
