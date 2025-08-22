import { defineStore } from 'pinia'
import { useModelStore } from './useModelStore';
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

export const useVoiceStore = defineStore('voice', {
  state: () => ({
    transcript: '',
    isListening: false,
    error: null as string | null,
    recognition: null as SpeechRecognition | null,
    isSpeaking: true,
  }),

  actions: {
    // 初始化语音识别
    initRecognition(): boolean {
      if (!('webkitSpeechRecognition' in window || 'SpeechRecognition' in window)) {
        this.error = '您的浏览器不支持语音识别功能';
        return false;
      }

      const SpeechRecognition = window.SpeechRecognition || window.webkitSpeechRecognition;
      this.recognition = new SpeechRecognition();

      this.recognition.lang = 'zh-CN';
      this.recognition.interimResults = false;
      this.recognition.maxAlternatives = 1;
      this.recognition.continuous = true; // 持续监听直到手动停止

      this.recognition.onresult = (event: SpeechRecognitionEvent) => {
        if (event.results.length > 0) {
          this.transcript = event.results[event.results.length - 1][0].transcript;
        }
      };

      this.recognition.onerror = (event: SpeechRecognitionErrorEvent) => {
        this.error = `语音识别错误：${event.error}`;
        this.stopRecognition();
      };

      this.recognition.onend = () => {
        this.isListening = false;
      };

      return true;
    },

    // 开始识别
    startRecognition(): void {
      if (this.isListening) return;

      if (!this.recognition && !this.initRecognition()) {
        return;
      }

      try {
        this.recognition!.start();
        this.isListening = true;
        this.error = null;
        this.transcript = '';
      } catch (err) {
        this.error = `启动失败：${(err as Error).message}`;
      }
    },

    // 停止识别
    stopRecognition(): void {
      if (this.recognition && this.isListening) {
        this.recognition.stop();
      }
    },

    // 重置状态
    resetTranscript(): void {
      this.transcript = '';
      this.error = null;
    },

    // 设置是否正在说话
    openSpeaking() {
      this.isSpeaking = true
    },

    // 设置是否停止说话
    closeSpeaking() {
      const modelStore = useModelStore();
      modelStore.stopSpeaking();
      this.isSpeaking = false
    }
  }
});
