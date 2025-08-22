<script setup lang="ts">
import { ref, onMounted, onBeforeUnmount } from 'vue'
import { useVoiceStore } from '@/stores/useVoiceStore'
import { useModelStore } from '@/stores/useModelStore'
import SendSVG from '@/assets/img/send.svg'
import VoiceSVG from '@/assets/img/voice.svg'
import VoiceOffSVG from '@/assets/img/voice-off.svg'
import RefreshSVG from '@/assets/img/refresh.svg'
const voiceStore = useVoiceStore()
const modelStore = useModelStore()
const isVoiceKeyPressed = ref(false)

const handleInput = () => {
  if (voiceStore.error) voiceStore.error = ''
}
// 键盘按下事件：监听 ctrl+q 键按下
const handleKeyDown = (event: KeyboardEvent) => {
  if (event.ctrlKey && event.code === 'KeyQ' && !isVoiceKeyPressed.value) {
    modelStore.stopSpeaking() // 停止语音输出
    isVoiceKeyPressed.value = true
    voiceStore.startRecognition()
  }
}

// 键盘释放事件：监听 ctrl+q 键松开
const handleKeyUp = (event: KeyboardEvent) => {
  if (!event.ctrlKey && !(event.code === 'KeyQ') && isVoiceKeyPressed.value) {
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

const toggleSpeech = () => {
  if (voiceStore.isSpeaking) {
    voiceStore.closeSpeaking()
  } else {
    voiceStore.openSpeaking()
  }
}

const resetHistory = () => {
  modelStore.resetCallHistory()
}

// 生命周期：组件挂载时添加事件监听器
onMounted(() => {
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
            <button class="reset-button" @click="resetHistory" title="清空历史">
              <img :src="RefreshSVG" class="w-[1.2vw] h-[1.2vw]" alt="重置" />
            </button>
            <button
              class="speak-button"
              :class="{ active: voiceStore.isSpeaking }"
              @click="toggleSpeech"
              title="播放/暂停语音"
            >
              <img
                :src="voiceStore.isSpeaking ? VoiceSVG : VoiceOffSVG"
                class="w-[1.2vw] h-[1.2vw]"
                alt="播放状态"
              />
            </button>
            <button class="send-button" title="发送" @click="snedMessage">
              <img :src="SendSVG" class="w-[1.2vw] h-[1.2vw]" alt="" />
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
  justify-content: space-between;
  align-items: center;
  gap: 1vw;
  padding: 1vw 1vw;
  height: 40vh;
  border-radius: 1vw;
  width: 100%;
  margin: 0 auto;
  background: linear-gradient(135deg, #f5f7fa 0%, #e4edf5 100%);
  box-shadow: 0 0.5vw 1.5vw rgba(0, 0, 0, 0.08);
}

.voice-button {
  position: relative;
  width: 100%;
  padding: 1.25vw;
  font-size: 1.1vw;
  font-weight: 600;
  color: white;
  background: linear-gradient(45deg, #6366f1, #8b5cf6);
  border: none;
  border-radius: 0.75vw;
  cursor: pointer;
  box-shadow: 0 0.25vw 0.75vw rgba(99, 102, 241, 0.3);
}

.voice-button:hover {
  transform: translateY(-0.02vw);
  box-shadow: 0 0.5vw 1vw rgba(99, 102, 241, 0.4);
}

.voice-button:active {
  transform: translateY(0.015vw);
}

.voice-button.listening {
  background: linear-gradient(45deg, #10b981, #06b6d4);
  animation: pulse 1.5s infinite;
}

.key-hint {
  display: block;
  font-size: 0.85vw;
  margin-top: 0.5vw;
  opacity: 0.8;
}

.transcript-box {
  width: 100%;
  height: 25vh;
  padding: 1vw;
  background: white;
  border-radius: 0.75vw;
  border: 0.015vw solid #e2e8f0;
  box-shadow: inset 0 0.15vw 0.35vw rgba(0, 0, 0, 0.05);
}

.edit-container {
  display: flex;
  flex-direction: column;
  gap: 0.5vw;
}

.edit-textarea {
  width: 100%;
  height: 15vh;
  padding: 0.2vw;
  border: none;
  border-radius: 0.75vw;
  resize: none;
  font-family: inherit;
  font-size: 1vw;
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
  margin-top: 0.75vw;
  flex-wrap: wrap;
}
.edit-buttons {
  display: flex;
  justify-content: flex-end;
  gap: 0.5vw;
}

.send-button {
  display: flex;
  align-items: center;
  justify-content: center;
  width: 2vw;
  height: 2vw;
  padding: 0;
  border-radius: 50%;
  background: linear-gradient(45deg, #6366f1, #8b5cf6);
  color: white;
  border: none;
  cursor: pointer;
}

.send-button:hover {
  background: linear-gradient(45deg, #6366f1, #8b5cf6);
  transform: scale(1.1);
}

.speak-button,
.reset-button {
  width: 2vw;
  height: 2vw;
  border-radius: 50%;
  background: linear-gradient(45deg, #FF9A9E 0%, #FAD0C4 100%);
  display: flex;
  align-items: center;
  justify-content: center;
  cursor: pointer;
}

.speak-button.active {
  background: linear-gradient(45deg, #6366f1, #8b5cf6);
  color: white;
}

.speak-button:hover,
.reset-button:hover {
  transform: scale(1.1);
}
.send-button svg {
  width: 1.3vw;
  height: 1.3vw;
  stroke: white;
}

.error-text {
  color: #ef4444;
  font-weight: 500;
  margin: 0;
}

@keyframes pulse {
  0% {
    box-shadow: 0 0 0 0 rgba(16, 185, 129, 0.4);
  }
  70% {
    box-shadow: 0 0 0 0.75vw rgba(16, 185, 129, 0);
  }
  100% {
    box-shadow: 0 0 0 0 rgba(16, 185, 129, 0);
  }
}
</style>
