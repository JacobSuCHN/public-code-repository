import { defineStore } from 'pinia'
import { useLive2DStore } from './useLive2DStore'

interface ModelResult {
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

export const useModelStore = defineStore('model', {
  state: () => ({
    callHistory: [] as ModelResult[],
    currentIndex: 0, // 新增：当前选中项的索引
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

    // 新增：设置当前选中索引
    setCurrentIndex(index: number) {
      if (index >= 0 && index < this.callHistory.length) {
        this.currentIndex = index
      }
    },

    async getResult(input: string) {
      this.stopSpeaking()
      const newItem: ModelResult = {
        input,
        result: '生成中...',
        timestamp: new Date()
      }
      this.callHistory.unshift(newItem)
      this.setCurrentIndex(0)  // 新增：自动选中最新项

      try {
        const res = await fetch('/api/chat', {
          method: 'POST',
          headers: { 'Content-Type': 'application/json' },
          body: JSON.stringify({ message: input })
        })

        const data = await res.json()
        const finalResult = data?.content || '生成失败'

        this.callHistory[0] = {
          ...this.callHistory[0],
          result: finalResult
        }

        if (data?.content) speakText(finalResult)
      } catch (err) {
        this.callHistory[0].result = '生成失败'
        console.error("API  请求失败:", err)
      }
    }
  },
  getters: {
    getCallHistory: (state) => state.callHistory,
    getCurrentIndex: (state) => state.currentIndex,  // 新增

    // 修改：获取当前选中项
    getCurrentResult: (state) => {
      if (state.callHistory.length === 0) return null
      return state.callHistory[state.currentIndex]
    },

    // 保留原有功能
    getLastCall: (state) => {
      if (state.callHistory.length === 0) return null
      return state.callHistory[state.callHistory.length - 1]
    }
  }
})
