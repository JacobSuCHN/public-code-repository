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
const markdownContent = `## 2.2.关于拍摄和操作的名词

- 拍摄格式：RAW/JPG

| 格式                                     | RAW                                                                                                                                     | JPG                                                                           |
| :--------------------------------------- | :-------------------------------------------------------------------------------------------------------------------------------------- | :---------------------------------------------------------------------------- |
| 定义                                     | 一种记录了数码相机传感器的原始信息，同时记录了由相机拍摄所产生的一些元数据（Metadata，如 ISO 的设置、快门速度、光圈值、白平衡等）的文件 | 一种针对照片影像而广泛使用的有损压缩标准方法，JPEG 格式是最常用的图像文件格式 |
| 是否有损                                 | 无损，原始数据                                                                                                                          | 有损，压缩                                                                    |
| 是否可以存留自定义风格信息（如色彩风格） | 否                                                                                                                                      | 是                                                                            |
| 优缺点                                   | 体积大，信息全面，后期调整空间大，原始                                                                                                  | 体积小，有损，后期调整空间小，有调整                                          |
| 后缀名                                   | .CR2 .ARW .DNG .NEF                                                                                                                     | .jpg                                                                          |

![](https://image.jslog.net/online/a-54/2025/02/06/14.png)

> “直出”的照片，JPG 的观感可能会好过 RAW，因为 JPG 会有机内的优化调整

- 联机拍摄与远程监看软件
  - 联机拍摄：Capture One
  - 远程操控：Canon Camera Connect、尼享 SnapBridge、Imaging Edge Mobile
    - 遥控拍摄
    - 遥控合影
    - 传输照片

# 3.基础操作

## 3.1.设置相机思路

- 通用设置思路
  - 设置双卡记录
  - 设置 RAW 格式记录
  - 关闭长时间曝光降噪
  - 自定义符合个人习惯的设置
`;
const DELIMITER = '$$$SPLIT$$$';
// 代理 OpenAI 聊天接口
app.post("/api/chat", async (req, res) => {
  try {
    const { message } = req.body;

    res.setHeader("Content-Type", "text/event-stream");
    res.setHeader("Cache-Control", "no-cache");
    res.setHeader("Connection", "keep-alive");

    const stream = await openai.chat.completions.create({
      model: "qwen-plus",
      messages: [{ role: "user", content: message }],
      stream: true, // 启用流式输出
    });

    // 逐个 chunk 返回
    for await (const chunk of stream) {
      const content = chunk.choices[0]?.delta || {};
      res.write(JSON.stringify(content)+DELIMITER);
    }

    res.end(); // 结束流
  } catch (error) {
    console.error("OpenAI  API Error:", error);
    res.status(500).json({ error: error.message });
  }
});

app.get("/api/chart", async (req, res) => {
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
