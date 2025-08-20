import { defineStore } from 'pinia'

interface ModelResult {
  input: string
  result: string
  timestamp: Date
}

let currentUtterance: SpeechSynthesisUtterance | null = null
function speakText(text: string) {
  if (currentUtterance) {
    window.speechSynthesis.cancel()
  }
  const utterance = new SpeechSynthesisUtterance(text)
  utterance.lang = 'zh-CN' // 中文
  utterance.rate = 1.2 // 语速（0.1-10）
  utterance.volume = 0.8 // 音量（0-1）

  currentUtterance = utterance
  window.speechSynthesis.speak(utterance)
}
export const useModelStore = defineStore('model', {
  state: () => ({
    callHistory: [] as ModelResult[],
  }),
  actions: {
    stopSpeaking() {
      if (currentUtterance) {
        window.speechSynthesis.cancel()
        currentUtterance = null
      }
    },
    async getResult(input: string) {
      this.stopSpeaking()
      const newItem: ModelResult = {
        input,
        result: '生成中...', // 初始状态
        timestamp: new Date()
      }
      this.callHistory.unshift(newItem)
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
        // 更新失败状态
        this.callHistory[0].result = '生成失败'
        console.error("API 请求失败:", err)
      }
    }
  },
  getters: {
    getCallHistory: (state) => state.callHistory,

    getLastCall: (state) => {
      if (state.callHistory.length === 0) return null
      return state.callHistory[state.callHistory.length - 1]
    }
  }
})
