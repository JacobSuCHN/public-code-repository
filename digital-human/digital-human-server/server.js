require("dotenv").config();
const express = require("express");
const { OpenAI } = require("openai");
const cors = require("cors");

const app = express();
app.use(cors());
app.use(express.json()); // 解析 JSON 请求体

const openai = new OpenAI({
  apiKey: process.env.OPENAI_API_KEY,
  baseURL: "https://dashscope.aliyuncs.com/compatible-mode/v1",
});
const markdownContent = `## 🎯 一、需求分析

### 核心功能

1. **语音交互**：用户通过语音输入与数字人进行对话
2. **数字人回答**：通过调用通义千问的API获取回答内容
3. **动态数据展示**：回答信息通过Markdown渲染在页面上
4. **页面布局**：左右两侧分别为表格和渲染区域，中间为对话窗口

------

## 🧩 二、页面设计

### 页面布局结构

![digital-human-sketch.png](https://cdn.jsdelivr.net/gh/JacobSuCHN/picgo-img/2025%2F08%2F22%2F13-07-01-63577591bd20282b60a12618774b8240-digital-human-sketch-e135b4.png)


------

## 🛠️ 三、技术实现

### 技术栈选择

| 模块         | 技术/框架                    |
| ---------- | ------------------------ |
| 前端框架       | Vue3 + Vite + TypeScript |
| 状态管理       | Pinia                    |
| CSS样式      | Tailwindcss              |
| Markdown渲染 | md-editor-v3             |
| 语音识别       | Web Speech API           |
| 大模型      | 通义千问                     |
| 后端框架       | Express                  |

------

## 📦 四、前端页面开发

### 1. 页面结构
- 组件划分结构
  - \`HomePage.vue\`
  - \`LeftComponent.vue\`
  - \`RightComponent.vue\`
  - \`MiddleComponent.vue\`
- 通用组件
  - \`Live2D.vue\`
  - \`MarkdownPreview.vue\`
  - \` VoiceInput.vue\`

### 2. 实现语音功能
- 创建一个语音管理模块
- 使用浏览器原生 Web Speech API
- 添加语音按钮控制逻辑
- 添加语音输出功能

### 3. 对话交互逻辑
- 创建一个对话管理模块
- 对话模块获取语音输入的结果
- 根据输入调用后台大模型接口，并记录调用历史

### 4.数字人渲染
- 创建一个数字人模块
- 根据对话模块调用结果，调用语音模块语音输出功能
- 数字人使用live2D模拟

### 5. Markdown 渲染
- 创建一个文章管理模块
- 调用后台接口获取 \`Markdown\` 文章
- 使用 \`md-editor-v3\` 渲染 \`Markdown\` 文章


------

## 🧪 五、后端接口设计
### 1.服务搭建
- 引入 \`express\` 、\`cors\`、\`dotenv\` 、\`openai\` 核心包
- 为避免通义千问 \`apiKey\` 暴露，设置系统变量（Windows）
- 服务器安装 \`pm2\`，方便服务启停

### 2.对话接口设计
- 调用通义千问API
- 流式输出返回值

### 3.文章接口设计
- 准备相应文章
- 输出该文章

------

## 📅 六、开发时间安排

| 时间  | 任务                     |
| --- | ---------------------- |
| 周一  | 设计页面草图                 |
| 周二  | 搭建Vue3项目，完成页面结构与基础组件   |
| 周三  | 实现语音识别与对话交互模块，完成后台接口开发 |
| 周四  | 实现Markdown渲染，优化页面内容    |
| 周五  | 整体测试，准备演示Demo          |
`;
const DELIMITER = "$$$SPLIT$$$";
// 代理 OpenAI 聊天接口
app.post("/api/chat", async (req, res) => {
  try {
    const { messages } = req.body;

    res.setHeader("Content-Type", "text/event-stream");
    res.setHeader("Cache-Control", "no-cache");
    res.setHeader("Connection", "keep-alive");

    const stream = await openai.chat.completions.create({
      model: "qwen-plus",
      stream: true, // 启用流式输出
      messages,
    });

    // 逐个 chunk 返回
    for await (const chunk of stream) {
      const content = chunk.choices[0]?.delta || {};
      res.write(JSON.stringify(content) + DELIMITER);
    }

    res.end(); // 结束流
  } catch (error) {
    console.error("OpenAI  API Error:", error);
    res.status(500).json({ error: error.message });
  }
});

app.get("/api/article", async (req, res) => {
  try {
    res.json({
      content: markdownContent,
    });
  } catch (error) {
    res.status(500).json({ error: error.message });
  }
});

const PORT = process.env.PORT || 3000;
app.listen(PORT, () => {
  console.log(`Server  running on http://localhost:${PORT}`);
});
