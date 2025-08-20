import { defineStore } from 'pinia'
import { ref } from 'vue'

interface SpeechRecognition extends EventTarget {
  lang: string;
  interimResults: boolean;
  maxAlternatives: number;
  continuous: boolean;
  start: () => void;
  stop: () => void;
  onresult: (event: SpeechRecognitionEvent) => void;
  onerror: (event: SpeechRecognitionErrorEvent) => void;
  onend: () => void;
}

declare global {
  interface Window {
    SpeechRecognition: { new(): SpeechRecognition };
    webkitSpeechRecognition: { new(): SpeechRecognition };
  }
}

interface SpeechRecognitionEvent extends Event {
  results: SpeechRecognitionResultList;
}

interface SpeechRecognitionErrorEvent extends Event {
  error: string;
}

interface SpeechRecognitionResultList {
  length: number;
  [index: number]: SpeechRecognitionResult;
}

interface SpeechRecognitionResult {
  [index: number]: SpeechRecognitionAlternative;
  0: SpeechRecognitionAlternative;
}

interface SpeechRecognitionAlternative {
  transcript: string;
}

export const useVoiceStore = defineStore('voice', () => {
  const transcript = ref<string>('')
  const isListening = ref<boolean>(false)
  const error = ref<string | null>(null)
  let recognition: SpeechRecognition | null = null

  // 初始化语音识别
  const initRecognition = (): boolean => {
    if (!('webkitSpeechRecognition' in window || 'SpeechRecognition' in window)) {
      error.value = '您的浏览器不支持语音识别功能'
      return false
    }

    const SpeechRecognition = window.SpeechRecognition || window.webkitSpeechRecognition
    recognition = new SpeechRecognition()

    recognition.lang = 'zh-CN'
    recognition.interimResults = false
    recognition.maxAlternatives = 1
    recognition.continuous = true // 持续监听直到手动停止

    recognition.onresult = (event: SpeechRecognitionEvent) => {
      if (event.results.length > 0) {
        transcript.value = event.results[event.results.length - 1][0].transcript
      }
    }

    recognition.onerror = (event: SpeechRecognitionErrorEvent) => {
      error.value = `语音识别错误：${event.error}`
      stopRecognition()
    }

    recognition.onend = () => {
      isListening.value = false
    }

    return true
  }

  // 开始识别
  const startRecognition = (): void => {
    if (isListening.value) return

    if (!recognition && !initRecognition()) {
      return
    }

    try {
      recognition!.start()
      isListening.value = true
      error.value = null
      transcript.value = ''
    } catch (err) {
      error.value = `启动失败：${(err as Error).message}`
    }
  }

  // 停止识别
  const stopRecognition = (): void => {
    if (recognition && isListening.value) {
      recognition.stop()
    }
  }

  // 重置状态
  const resetTranscript = (): void => {
    transcript.value = ''
    error.value = null
  }

  return {
    transcript,
    isListening,
    error,
    startRecognition,
    stopRecognition,
    resetTranscript
  }
})
