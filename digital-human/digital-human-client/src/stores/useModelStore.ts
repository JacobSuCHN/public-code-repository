import { defineStore } from 'pinia'
import { useLive2DStore } from './useLive2DStore'
import { useVoiceStore } from './useVoiceStore'

const DELIMITER = '$$$SPLIT$$$'

// 接口定义
export interface Model {
  role: string
  content: string
}

export interface ModelResult {
  id: string
  input: string
  result: string
  timestamp: Date
  isLoading: boolean
  success?: boolean
  isProcessing?: boolean
}

let currentUtterance: SpeechSynthesisUtterance | null = null

function speakText(text: string) {
  const voiceStore = useVoiceStore()
  const live2dStore = useLive2DStore()

  if (currentUtterance) {
    window.speechSynthesis.cancel()
    live2dStore.stopSpeak()
  }

  if (!voiceStore.isSpeaking) return

  live2dStore.startSpeak()

  const utterance = new SpeechSynthesisUtterance(text)
  utterance.lang = 'zh-CN'
  utterance.rate = 1.2
  utterance.volume = 0.8

  utterance.onend = () => {
    live2dStore.stopSpeak()
    currentUtterance = null
  }

  utterance.onerror = () => {
    live2dStore.stopSpeak()
    currentUtterance = null
  }

  currentUtterance = utterance
  window.speechSynthesis.speak(utterance)
}

function generateUniqueId(): string {
  return Date.now().toString(36) + Math.random().toString(36).substring(2, 9)
}

function loadFromLocalStorage(): ModelResult[][] {
  const saved = localStorage.getItem('chatListHistory')
  return saved ? JSON.parse(saved) : [[]]
}

function saveToLocalStorage(history: ModelResult[][]) {
  localStorage.setItem('chatListHistory', JSON.stringify(history))
}

export const useModelStore = defineStore('model', {
  state: () => ({
    chatList: [] as Model[],
    chatListHistory: loadFromLocalStorage() as ModelResult[][], // 从 localStorage 加载
    currentSessionIndex: 0,
    currentIndex: 0,
    isProcessing: false
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
      if (this.currentIndex !== index) this.stopSpeaking()
      const session = this.chatListHistory[this.currentSessionIndex]
      if (index >= 0 && index < session.length) this.currentIndex = index
    },
    setCurrentSessionIndex(index: number) {
      if (this.currentSessionIndex !== index) this.stopSpeaking()
      if (index >= 0 && index < this.chatListHistory.length) this.currentSessionIndex = index
    },

    createNewChat() {
      this.stopSpeaking()
      const currentSession = this.chatListHistory[this.currentSessionIndex]
      if (currentSession.length == 0) return
      this.chatListHistory.push([])
      this.currentSessionIndex = this.chatListHistory.length - 1
      this.currentIndex = 0
      this.chatList = []
    },

    async getResult(input: string) {
      this.isProcessing = true
      this.stopSpeaking()
      const uniqueId = generateUniqueId()

      const newItem: ModelResult = {
        id: uniqueId,
        input,
        result: '生成中...',
        timestamp: new Date(),
        isLoading: true,
        success: false,
        isProcessing: true
      }
      const session = this.chatListHistory[this.currentSessionIndex]
      session.push(newItem)
      this.setCurrentIndex(0)
      this.chatList = [
        ...session.flatMap(item => [
          { role: 'user', content: item.input },
          { role: 'assistant', content: item.result }
        ]),
        { role: 'user', content: input }
      ];
      this.saveHistory()

      try {
        const res = await fetch('/api/chat', {
          method: 'POST',
          headers: { 'Content-Type': 'application/json' },
          body: JSON.stringify({ messages: this.chatList })
        })

        if (!res.ok || !res.body) {
          this.handleError(uniqueId, '网络错误，请稍后再试')
          throw new Error('网络响应异常')
        }

        const reader = res.body.getReader()
        const decoder = new TextDecoder()
        let accumulatedText = ''

        const targetIndex = session.findIndex(item => item.id === uniqueId)
        while (true) {
          const { done, value } = await reader.read()
          if (done) break

          const chunk = decoder.decode(value, { stream: true })
          const lines = chunk.split(DELIMITER).filter(line => line.trim())

          for (const line of lines) {
            try {
              const data = JSON.parse(line)
              accumulatedText += data.content
              if (targetIndex !== -1) {
                session[targetIndex].isProcessing = false
                session[targetIndex].result = accumulatedText
                this.saveHistory()
              }
            } catch (e) {
              console.error('JSON  解析失败:', e)
            }
          }
        }

        if (targetIndex !== -1) {
          session[targetIndex].isLoading = false
          session[targetIndex].success = true
          this.chatList.push({ role: 'assistant', content: accumulatedText })
          this.saveHistory()
        }

        if (accumulatedText && this.currentIndex === targetIndex) {
          speakText(accumulatedText)
        }

      } catch (err) {
        this.handleError(uniqueId, '生成失败')
        console.error('API  请求失败:', err)
      } finally {
        this.isProcessing = false
        useVoiceStore().error = ''
      }
    },

    handleError(id: string, message: string) {
      const session = this.chatListHistory[this.currentSessionIndex]
      const index = session.findIndex(item => item.id === id)
      if (index !== -1) {
        session[index].result = message
        session[index].isLoading = false
        session[index].success = false
        session[index].isProcessing = false
        this.saveHistory()
      }
    },

    saveHistory() {
      saveToLocalStorage(this.chatListHistory)
    }
  },
  getters: {
    getCallHistory: state => state.chatListHistory,
    getCurrentSession: state => state.chatListHistory[state.currentSessionIndex] || [],
    getCurrentResult: state => {
      const session = state.chatListHistory[state.currentSessionIndex]
      return session[state.currentIndex] || null
    },
    getLastCallInSession: state => {
      const session = state.chatListHistory[state.currentSessionIndex]
      return session.length ? session[session.length - 1] : null
    },
    getAllSessions: (state) => {
      return state.chatListHistory.map((session, idx) => {
        const lastItem = session.length ? session[session.length - 1] : null
        return {
          sessionId: idx,
          count: session.length,
          latest: lastItem ? lastItem.timestamp : null,
          input: lastItem ? lastItem.input : '无输入',
          result: lastItem ? lastItem.result : '',
          isLoading: lastItem ? lastItem.isLoading : false,
          success: lastItem ? lastItem.success : false,
          isProcessing: lastItem ? lastItem.isProcessing : false
        }
      })
    }
  }
})
