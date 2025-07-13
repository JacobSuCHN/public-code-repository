import "./index.css";
import React from "react";
interface Props {
  title?: string;
  children?: React.ReactNode;
  callback?: (params: string) => void;
}
// 第一种写法：interface 赋给 props
// export default function Card1(props:Props){
//   return <div className='card'>
//     <header>
//       <div>{props.title}</div>
//       <div>副标题</div>
//     </header>
//     <main>
//       内容区域
//     </main>
//     <footer>
//       <button>确认</button>
//       <button>取消</button>
//     </footer>
//   </div>
// }
// 第二种写法：React.FC<Props> 赋给组件

// 默认值
// 1.解构 {title='默认标题'}
// 2.声明一个默认对象
const defaultProps: Partial<Props> = {
  title: "默认标题",
};
declare global {
  interface Event {
    params: {
      name: string;
    };
  }
}
const Card1: React.FC<Props> = (props) => {
  // 创建自定义事件
  const e = new Event("on-card");
  const clickTap = () => {
    e.params = { name: "card1" };
    // 派发事件
    window.dispatchEvent(e);
  };

  const { title } = { ...defaultProps, ...props };
  return (
    <div className="card">
      <header>
        <div>{title}</div>
        <div>副标题</div>
      </header>
      <main>{props.children}</main>
      <footer>
        <button onClick={clickTap}>确认</button>
        <button>取消</button>
      </footer>
    </div>
  );
};

export default Card1;
