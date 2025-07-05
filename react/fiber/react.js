const React = {
  createElement(type, props = {}, ...children) {
    return {
      type,
      props: {
        ...props,
        children: children.map((child) => {
          if (typeof child === "object") {
            return child;
          } else {
            return React.createTextElement(child);
          }
        }),
      },
    };
  },
  createTextElement(text) {
    return {
      type: "TEXT_ELEMENT",
      props: {
        nodeValue: text,
        children: [],
      },
    };
  },
};
let nextUnitOfWork = null; // 下一个工作单元
let wipRoot = null; // 工作中的 Fiber 树
let currentRoot = null; // 当前 Fiber 树
let deletions = []; // 删除的 Fiber 列表
function render(element, container) {
  wipRoot = {
    dom: container, // 容器 DOM
    props: { children: [element] }, // 根元素的属性
    alternate: currentRoot, // 当前 Fiber 树
    type: "ROOT", // 根节点类型
  };
  nextUnitOfWork = wipRoot; // 设置下一个工作单元为根节点
  deletions = []; // 清空删除列表
}

function createFiber(element, parent) {
  return {
    type: element.type, // 元素类型
    props: element.props, // 元素属性
    dom: null, // DOM 元素尚未创建
    parent: parent, // 父节点
    child: null, // 子节点
    sibling: null, // 兄弟节点
    alternate: null, // 旧的 Fiber 节点
    effectTag: null, // 副作用标记
  };
}
function createDom(fiber) {
  const dom =
    fiber.type === "TEXT_ELEMENT"
      ? document.createTextNode("")
      : document.createElement(fiber.type); // 创建 DOM 元素
  updateDom(dom, {}, fiber.props); // 更新 DOM 属性
  return dom;
}
function updateDom(dom, prevProps, nextProps) {
  // 删除旧的属性
  Object.keys(prevProps)
    .filter((name) => name !== "children")
    .filter((name) => prevProps[name] !== nextProps[name])
    .forEach((name) => {
      dom[name] = "";
    });
  // 添加新的属性
  Object.keys(nextProps)
    .filter((name) => name !== "children")
    .forEach((name) => {
      dom[name] = nextProps[name];
    });
}
function workLoop(deadline) {
  let shouldYield = false; // 是否需要让出控制权
  // 如果没有下一个工作单元，且有工作中的 Fiber 树，设置下一个工作单元为工作中的 Fiber 树
  while (nextUnitOfWork && !shouldYield) {
    nextUnitOfWork = performUnitOfWork(nextUnitOfWork); // 执行当前工作单元
    shouldYield = deadline.timeRemaining() < 1; // 检查是否有足够的时间继续执行
  }
  // 如果没有下一个工作单元且有工作中的 Fiber 树，提交 Fiber 树
  if (!nextUnitOfWork && wipRoot) {
    commitRoot(); // 提交工作中的 Fiber 树
  }
  requestIdleCallback(workLoop); // 如果还有工作单元，继续在空闲时间执行
}
requestIdleCallback(workLoop); // 利用浏览器空闲时间执行工作循环
function performUnitOfWork(fiber) {
  if (!fiber.dom) {
    fiber.dom = createDom(fiber); // 创建 DOM 元素
  }
  // 遍历子节点
  reconcileChildren(fiber, fiber.props.children);
  // 如果有子节点，返回第一个子节点作为下一个工作单元
  if (fiber.child) {
    return fiber.child; // 返回第一个子节点作为下一个工作单元
  }
  let nextFiber = fiber; // 当前工作单元
  // 向上查找兄弟节点
  while (nextFiber) {
    if (nextFiber.sibling) {
      return nextFiber.sibling; // 返回兄弟节点作为下一个工作单元
    }
    nextFiber = nextFiber.parent; // 向上查找父节点
  }
  return null; // 没有更多工作单元
}
function reconcileChildren(wipFiber, elements) {
  // 形成fiber树，并实现diff算法
  let index = 0; // 当前元素索引
  let prevSibling = null; // 上一个兄弟节点
  let oldFiber = wipFiber.alternate && wipFiber.alternate.child; // 获取旧的子节点
  // 删除列表，用于存储需要删除的 Fiber 节点
  while (index < elements.length || oldFiber != null) {
    const element = elements[index]; // 获取当前元素
    // 1.如果旧的子节点存在且类型匹配，复用旧的节点
    const sameType = oldFiber && element && oldFiber.type === element.type;
    let newFiber = null; // 新的 Fiber 节点
    // 如果旧的子节点存在且类型匹配，复用旧的节点
    if (sameType) {
      newFiber = {
        type: oldFiber.type, // 复用旧的类型
        props: element.props, // 更新属性
        dom: oldFiber.dom, // 复用旧的 DOM 元素
        parent: wipFiber, // 设置父节点
        alternate: oldFiber, // 保留旧的 Fiber
        effectTag: "UPDATE", // 标记为更新
      };
    }
    // 2.如果旧的子节点不存在，创建新的节点
    if (element && !sameType) {
      newFiber = createFiber(element, wipFiber); // 创建新的 Fiber 节点
      newFiber.effectTag = "PLACEMENT"; // 标记为放置
    }
    // 3.如果旧的子节点存在但类型不匹配，删除旧的节点
    if (oldFiber && !sameType) {
      oldFiber.effectTag = "DELETION"; // 标记为删除
      deletions.push(oldFiber); // 添加到删除列表
    }
    if (oldFiber) {
      oldFiber = oldFiber.sibling; // 移动到下一个旧的兄弟节点
    }

    // 将新的 Fiber 节点添加到当前 Fiber 的子节点列表中
    // 如果是第一个子节点，直接设置为当前 Fiber 的子节点
    if (index == 0) {
      wipFiber.child = newFiber; // 第一个子节点
    } else if (element) {
      prevSibling.sibling = newFiber; // 设置兄弟节点
    }
    prevSibling = newFiber; // 更新上一个兄弟节点
    index++;
  }
}

function commitRoot() {
  deletions.forEach(commitWork); // 提交删除的 Fiber
  commitWork(wipRoot.child); // 提交工作中的 Fiber 树
  currentRoot = wipRoot; // 更新当前 Fiber 树
  wipRoot = null; // 清空工作中的 Fiber 树
}
function commitWork(fiber) {
  if (!fiber) {
    return; // 如果 Fiber 不存在，直接返回
  }
  const domParent = fiber.parent ? fiber.parent.dom : null; // 获取父节点的 DOM
  if (fiber.effectTag === "PLACEMENT" && fiber.dom) {
    domParent.appendChild(fiber.dom); // 将新创建的 DOM 元素添加到父节点
  } else if (fiber.effectTag === "UPDATE" && fiber.dom) {
    updateDom(fiber.dom, fiber.alternate.props, fiber.props); // 更新 DOM 元素的属性
  } else if (fiber.effectTag === "DELETION") {
    domParent.removeChild(fiber.dom); // 删除 DOM 元素
  }
  // 提交子节点
  commitWork(fiber.child);
  // 提交兄弟节点
  commitWork(fiber.sibling);
}

render(
  React.createElement(
    "div",
    { id: "test" },
    React.createElement("span", null, "js")
  ),
  document.getElementById("root")
);

setTimeout(() => {
  render(
    React.createElement(
      "div",
      { id: "test" },
      React.createElement("p", null, "react")
    ),
    document.getElementById("root")
  );
}, 2000);
