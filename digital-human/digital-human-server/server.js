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
const markdownContent =
  "以下是近10年（2015年至2024年）男子全程马拉松（Full Marathon）的世界最好成绩（即世界纪录）及其创造者的信息：\n\n---\n\n### 🏃‍♂️ 男子马拉松世界纪录演变（2015–2024）\n\n| 年份 | 运动员 | 国籍 | 比赛名称 | 成绩 | 备注 |\n|------|--------|------|-----------|-------|------|\n| **2018** | **Eliud Kipchoge**（埃鲁德·基普乔格） | 肯尼亚 | 柏林马拉松 | **2:01:39** | 打破原世界纪录（2:02:57） |\n| **2023** | **Kelvin Kiptum**（凯尔文·基普图姆） | 肯尼亚 | 芝加哥马拉松 | **2:00:35** | 新世界纪录（打破2:01大关） |\n\n---\n\n### 📌 说明：\n\n- **2015年之前**的世界纪录为 **Dennis Kimetto**（肯尼亚）于2014年在柏林马拉松创造的 **2:02:57**。\n- **2018年**，**基普乔格**（Eliud Kipchoge）在柏林马拉松以 **2:01:39** 刷新世界纪录，被认为是马拉松进入“2小时01分”时代的重要标志。\n- **2023年9月**，**凯尔文·基普图姆**（Kelvin Kiptum）在**芝加哥马拉松**以 **2:00:35** 创下新的世界纪录，成为首位在正式比赛中跑进**2小时01分**的选手。\n- 基普图姆在2024年2月因飞机失事不幸去世，年仅24岁。\n\n---\n\n### 🏆 其他值得一提的成绩：\n\n- **Breaking2 项目（2017年）**：基普乔格在NIKE组织的“破2计划”中，以**2:00:25**完成马拉松，但因非正式比赛、使用配速团队和设备辅助，**不被国际田联承认**为世界纪录。\n- **2020年伦敦马拉松**：Shura Kitata（埃塞俄比亚）以**2:05:44**夺冠，是当年最快的正式比赛成绩。\n- **2022年柏林马拉松**：基普乔格以**2:01:09**再次逼近世界纪录。\n\n---\n\n### 🧠 小知识：\n\n- 马拉松世界纪录的提升非常困难，每秒的进步都代表人类极限的突破。\n- 目前男子马拉松世界纪录为 **2:00:35**（凯尔文·基普图姆，2023年）。\n\n---\n\n如需了解女子马拉松纪录、各年份赛事成绩或不同国家选手表现，也可以继续问我！";
// 代理 OpenAI 聊天接口
app.post("/api/chat", async (req, res) => {
  try {
    const { message } = req.body;
    const completion = await openai.chat.completions.create({
      model: "qwen-plus",
      messages: [{ role: "user", content: message }],
    });
    res.json({ content: completion.choices[0].message.content });
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
