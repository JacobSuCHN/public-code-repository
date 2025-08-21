import { defineStore } from 'pinia'
import { useLive2DStore } from './useLive2DStore'


const DELIMITER = '$$$SPLIT$$$'; // 定义分隔符

// 增加唯一ID标识
interface ModelResult {
  id: string // 新增唯一标识符
  input: string
  result: string
  timestamp: Date
  isLoading: boolean
  success: boolean // 可选属性，表示是否成功
}

let currentUtterance: SpeechSynthesisUtterance | null = null
function speakText(text: string) {
  const live2dStore = useLive2DStore()
  if (currentUtterance) {
    window.speechSynthesis.cancel()
    live2dStore.stopSpeak()
  }
  live2dStore.startSpeak()
  const utterance = new SpeechSynthesisUtterance(text)
  utterance.lang = 'zh-CN'
  utterance.rate = 1.2
  utterance.volume = 0.8

  utterance.onend = () => live2dStore.stopSpeak()
  utterance.onerror = () => live2dStore.stopSpeak()

  currentUtterance = utterance
  live2dStore.startSpeak()
  window.speechSynthesis.speak(utterance)
}

// 生成唯一ID的工具函数
function generateUniqueId() {
  return Date.now().toString(36) + Math.random().toString(36).substring(2, 9)
}

export const useModelStore = defineStore('model', {
  state: () => ({
    callHistory: [] as ModelResult[],
    currentIndex: 0,
  }),
  actions: {
    stopSpeaking() {
      const live2dStore = useLive2DStore()
      if (currentUtterance) {
        live2dStore.stopSpeak()
        window.speechSynthesis.cancel()
        currentUtterance = null
      }
    },

    setCurrentIndex(index: number) {
      if (index >= 0 && index < this.callHistory.length) {
        this.currentIndex = index
      }
    },

    async getResult(input: string) {
      this.stopSpeaking();
      const uniqueId = generateUniqueId(); // 生成唯一ID

      const newItem: ModelResult = {
        id: uniqueId,
        input,
        result: '生成中...',
        timestamp: new Date(),
        isLoading: true,
        success: false,
      };

      this.callHistory.unshift(newItem);
      this.setCurrentIndex(0);

      try {
        const res = await fetch('/api/chat', {
          method: 'POST',
          headers: { 'Content-Type': 'application/json' },
          body: JSON.stringify({ message: input })
        });

        if (!res.ok || !res.body) {
          this.callHistory[0].result = '网络错误，请稍后再试';
          this.callHistory[0].isLoading = false;
          this.callHistory[0].success = false;
          throw new Error('Network response was not ok');
        }

        const reader = res.body.getReader();
        const decoder = new TextDecoder();
        let accumulatedText = '';
        const targetIndex = this.callHistory.findIndex(item => item.id === uniqueId);
        while (true) {
          const { done, value } = await reader.read();
          if (done) break;

          const chunk = decoder.decode(value, { stream: true });
          const lines = chunk.split(DELIMITER).filter(line => line.trim() !== '');

          for (const line of lines) {
            const dataStr = line;
            try {
              const data = JSON.parse(dataStr);
              accumulatedText += data.content;

              if (targetIndex !== -1) {
                this.callHistory[targetIndex].result = accumulatedText;
              }
            } catch (e) {
              console.error('JSON  解析失败:', e);
            }
          }
        }

        if (targetIndex !== -1) {
          this.callHistory[targetIndex].isLoading = false;
          this.callHistory[targetIndex].success = true;
        }

        if (accumulatedText && this.currentIndex === targetIndex) {
          speakText(accumulatedText);
        }

      } catch (err) {
        const targetIndex = this.callHistory.findIndex(item => item.id === uniqueId);
        if (targetIndex !== -1) {
          this.callHistory[targetIndex].result = '生成失败';
          this.callHistory[targetIndex].isLoading = false;
          this.callHistory[targetIndex].success = false;
        }
        console.error("API  请求失败:", err);
      }
    }
  },
  getters: {
    getCallHistory: (state) => state.callHistory,
    getCurrentIndex: (state) => state.currentIndex,

    getCurrentResult: (state) => {
      if (state.callHistory.length === 0) return null
      return state.callHistory[state.currentIndex]
    },

    getLastCall: (state) => {
      if (state.callHistory.length === 0) return null
      return state.callHistory[state.callHistory.length - 1]
    }
  }
})
