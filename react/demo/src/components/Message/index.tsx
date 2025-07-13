import ReactDom from 'react-dom/client';
import './index.css'
const Message = () => {
  return <div>消息提示</div>
}
interface Item {
  messageContainer: HTMLDivElement;
  root: ReactDom.Root;
}
const queue:Item[] = [];
window.onShow = () => {
  const messageContainer = document.createElement('div');
  messageContainer.className = 'message'
  messageContainer.style.top = `${queue.length * 50}px`;
  document.body.appendChild(messageContainer);
  // 容器关联Message组件
  // 把容器注册成根组件
  const root = ReactDom.createRoot(messageContainer);
  root.render(<Message />);
  queue.push({
    messageContainer,
    root
  });
  setTimeout(() => {
    const item = queue.find(item=>item.messageContainer === messageContainer)!;
    item.root.unmount();
    document.body.removeChild(item.messageContainer);
    queue.splice(queue.indexOf(item), 1);
  }, 2000);
}

// ts的声明扩充
declare global {
  interface Window {
    onShow: () => void;
  }
}

export default Message;