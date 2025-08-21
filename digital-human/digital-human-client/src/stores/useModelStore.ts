import { defineStore } from 'pinia'
import { useLive2DStore } from './useLive2DStore'

// 增加唯一ID标识
interface ModelResult {
  id: string // 新增唯一标识符
  input: string
  result: string
  timestamp: Date
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
      this.stopSpeaking()
      const uniqueId = generateUniqueId() // 生成唯一ID

      const newItem: ModelResult = {
        id: uniqueId, // 绑定唯一ID
        input,
        result: '生成中...',
        timestamp: new Date()
      }

      this.callHistory.unshift(newItem)
      this.setCurrentIndex(0)

      try {
        const res = await fetch('/api/chat', {
          method: 'POST',
          headers: { 'Content-Type': 'application/json' },
          body: JSON.stringify({ message: input })
        })

        const data = await res.json()
        const finalResult = data?.content || '生成失败'

        // 通过ID查找而非固定索引
        const targetIndex = this.callHistory.findIndex(item => item.id === uniqueId)
        if (targetIndex !== -1) {
          // 安全更新指定记录
          this.callHistory[targetIndex].result = finalResult
        }

        if (data?.content&&targetIndex==this.currentIndex) speakText(finalResult)
      } catch (err) {
        const targetIndex = this.callHistory.findIndex(item => item.id === uniqueId)
        if (targetIndex !== -1) {
          this.callHistory[targetIndex].result = '生成失败'
        }
        console.error("API  请求失败:", err)
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
