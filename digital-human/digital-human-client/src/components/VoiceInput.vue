<script setup lang="ts">
import { ref, onMounted, onBeforeUnmount } from 'vue'
import { useVoiceStore } from '@/stores/useVoiceStore'
import { useModelStore } from '@/stores/useModelStore'

const voiceStore = useVoiceStore()
const modelStore = useModelStore()
const isVoiceKeyPressed = ref(false)
const textareaRef = ref<HTMLTextAreaElement | null>(null)

// 自动调整 textarea 高度
const autoResize = () => {
  const textarea = textareaRef.value
  if (textarea) {
    textarea.style.height = 'auto'
    textarea.style.height = `${textarea.scrollHeight}px`
  }
}
const handleInput = () => {
  if (voiceStore.error) voiceStore.error = ''
  autoResize()
}
// 键盘按下事件：监听 ctrl+q 键按下
const handleKeyDown = (event: KeyboardEvent) => {
  if (event.ctrlKey && event.code === "KeyQ" && !isVoiceKeyPressed.value) {
    modelStore.stopSpeaking() // 停止语音输出
    isVoiceKeyPressed.value = true
    voiceStore.startRecognition()
  }
}

// 键盘释放事件：监听 ctrl+q 键松开
const handleKeyUp = (event: KeyboardEvent) => {
  if (!event.ctrlKey && !(event.code === "KeyQ") && isVoiceKeyPressed.value) {
    isVoiceKeyPressed.value = false
    voiceStore.stopRecognition()
  }
}

// 发送消息
const snedMessage = () => {
  const trimmedText = voiceStore.transcript.trim()
  if (!trimmedText) {
    voiceStore.error = '请输入内容后再发送'
    return
  }
  modelStore.getResult(trimmedText)
  voiceStore.transcript = ''
  voiceStore.error = ''
}

// 生命周期：组件挂载时添加事件监听器
onMounted(() => {
  autoResize()
  window.addEventListener('keydown', handleKeyDown)
  window.addEventListener('keyup', handleKeyUp)
})

// 生命周期：组件卸载前移除事件监听器
onBeforeUnmount(() => {
  window.removeEventListener('keydown', handleKeyDown)
  window.removeEventListener('keyup', handleKeyUp)
  voiceStore.stopRecognition()
})
</script>

<template>
  <div class="voice-input-container">
    <!-- 语音按钮 -->
    <button
      class="voice-button"
      :class="{ listening: voiceStore.isListening }"
      @mousedown="voiceStore.startRecognition"
      @mouseup="voiceStore.stopRecognition"
      @touchstart="voiceStore.startRecognition"
      @touchend="voiceStore.stopRecognition"
    >
      🎙️ {{ voiceStore.isListening ? '正在聆听...' : '点击说话' }}
      <span v-if="isVoiceKeyPressed" class="key-hint">(Ctrl+Q键按住中)</span>
    </button>

    <!-- 识别结果展示与编辑区域 -->
    <div class="transcript-box">
      <div class="edit-container">
        <textarea
          ref="textareaRef"
          v-model="voiceStore.transcript"
          name="transcript"
          placeholder="识别结果将显示在这里..."
          class="edit-textarea"
          @input="handleInput"
          autofocus
        />
        <div class="edit-footer">
          <p class="error-text">{{ voiceStore.error }}</p>
          <div class="edit-buttons">
            <button class="send-button" title="发送" @click="snedMessage">
              <img src="@/assets/img/send.svg" class="w-6 h-6" alt="" />
            </button>
          </div>
        </div>
      </div>
    </div>
  </div>
</template>

<style scoped>
.voice-input-container {
  display: flex;
  flex-direction: column;
  align-items: center;
  gap: 1rem;
  padding: 1.5rem;
  border-radius: 16px;
  max-width: 480px;
  margin: 0 auto;
  background: linear-gradient(135deg, #f5f7fa 0%, #e4edf5 100%);
  box-shadow: 0 8px 24px rgba(0, 0, 0, 0.08);
}

.voice-button {
  position: relative;
  width: 100%;
  padding: 1.25rem;
  font-size: 1.1rem;
  font-weight: 600;
  color: white;
  background: linear-gradient(45deg, #6366f1, #8b5cf6);
  border: none;
  border-radius: 12px;
  cursor: pointer;
  transition: all 0.2s ease;
  box-shadow: 0 4px 12px rgba(99, 102, 241, 0.3);
}

.voice-button:hover {
  transform: translateY(-2px);
  box-shadow: 0 6px 16px rgba(99, 102, 241, 0.4);
}

.voice-button:active {
  transform: translateY(1px);
}

.voice-button.listening {
  background: linear-gradient(45deg, #10b981, #06b6d4);
  animation: pulse 1.5s infinite;
}

.key-hint {
  display: block;
  font-size: 0.85rem;
  margin-top: 0.5rem;
  opacity: 0.8;
}

.transcript-box {
  width: 100%;
  min-height: 120px;
  padding: 1.5rem;
  background: white;
  border-radius: 12px;
  border: 1px solid #e2e8f0;
  box-shadow: inset 0 2px 4px rgba(0, 0, 0, 0.05);
  transition: all 0.3s ease;
}

.edit-container {
  display: flex;
  flex-direction: column;
  gap: 0.5rem;
}

.edit-textarea {
  width: 100%;
  min-height: 80px;
  padding: 0.75rem;
  border: none;
  border-radius: 8px;
  resize: none;
  font-family: inherit;
  font-size: 1rem;
  line-height: 1.5;
  background: transparent;
}

.edit-textarea:focus {
  outline: none;
}

.edit-footer {
  display: flex;
  align-items: center;
  justify-content: space-between;
  margin-top: 8px;
  flex-wrap: wrap;
}
.edit-buttons {
  display: flex;
  justify-content: flex-end;
  gap: 0.5rem;
}

.send-button {
  display: flex;
  align-items: center;
  justify-content: center;
  width: 40px;
  height: 40px;
  padding: 0;
  border-radius: 50%;
  background: linear-gradient(45deg, #6366f1, #8b5cf6);
  color: white;
  border: none;
  cursor: pointer;
  transition: all 0.2s ease;
}

.send-button:hover {
  background: linear-gradient(45deg, #6366f1, #8b5cf6);
  transform: scale(1.1);
}

.send-button svg {
  width: 20px;
  height: 20px;
  stroke: white;
}

.error-text {
  color: #ef4444;
  font-weight: 500;
  margin: 0;
  transition: opacity 0.3s ease;
}

@keyframes pulse {
  0% {
    box-shadow: 0 0 0 0 rgba(16, 185, 129, 0.4);
  }
  70% {
    box-shadow: 0 0 0 12px rgba(16, 185, 129, 0);
  }
  100% {
    box-shadow: 0 0 0 0 rgba(16, 185, 129, 0);
  }
}
</style>
