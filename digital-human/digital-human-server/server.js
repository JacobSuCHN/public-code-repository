require('dotenv').config();
const express = require('express');
const { OpenAI } = require('openai');
const cors = require('cors');
 
const app = express();
app.use(cors()); 
app.use(express.json());   // 解析 JSON 请求体

const openai = new OpenAI({
  apiKey: process.env.OPENAI_API_KEY,
  baseURL: "https://dashscope.aliyuncs.com/compatible-mode/v1"
});
 
// 代理 OpenAI 聊天接口
app.post('/api/chat',  async (req, res) => {
  try {
    const { message } = req.body; 
    const completion = await openai.chat.completions.create({ 
      model: "qwen-plus",
      messages: [{ role: "user", content: message }],
    });
    res.json({  content: completion.choices[0].message.content  });
  } catch (error) {
    console.error('OpenAI  API Error:', error);
    res.status(500).json({  error: error.message  });
  }
});
 
// 健康检查接口 
app.get('/health',  (req, res) => {
  res.send('Service  is running');
});
 
const PORT = process.env.PORT || 3000;
app.listen(PORT,  () => {
  console.log(`Server  running on http://localhost:${PORT}`);
});