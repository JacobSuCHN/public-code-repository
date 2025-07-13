import "./index.css";
import React from "react";
interface Props {
  title?: string;
  children?: React.ReactNode;
  callback?: (params: string) => void;
}
// 第一种写法：interface 赋给 props
// export default function Card2(props:Props){
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
const Card2: React.FC<Props> = (props) => {
  // 接收派发
  window.addEventListener("on-card", (e) => {
    console.log("🚀 ~ e:", e);
  });
  const { title } = { ...defaultProps, ...props };
  return (
    <div className="card">
      <header>
        <div>{title}</div>
        <div>副标题</div>
      </header>
      <main>{props.children}</main>
      <footer>
        <button
          onClick={() => props.callback && props.callback("child params")}
        >
          确认
        </button>
        <button>取消</button>
      </footer>
    </div>
  );
};

export default Card2;
