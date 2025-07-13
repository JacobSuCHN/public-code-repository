import { createBrowserRouter } from "react-router";
import Home from "../pages/Home";
import Layout from "../layout";
const data = [
  {
    name: 'home',
    path: '/home'
  },
  {
    name: 'about',
    path: '/about'
  }
]
const sleep = (time: number) => new Promise((resolve) => setTimeout(resolve, time));
const router = createBrowserRouter([
  {
    path: '/',
    Component: Layout,
    children: [
      {
        path: 'home',
        Component: Home,
        loader: async () => {
          await sleep(2000); // 模拟加载
          // fetch ajax axios 获取数据
          return { data, success: true }
        },
        action: async ({ request }) => {
          const json = await request.json();
          console.log(json)
          data.push(json)
          await sleep(2000); // 模拟加载
          // fetch ajax axios 提交数据
          return { success: true, message: '提交成功' }
        }
      },
      {
        path: 'about',
        lazy: async () => {
          await sleep(5000); // 模拟加载
          const about = await import('../pages/About');
          return { Component: about.default }
        }, // 懒加载
      },
    ]
  },
]);

export default router;