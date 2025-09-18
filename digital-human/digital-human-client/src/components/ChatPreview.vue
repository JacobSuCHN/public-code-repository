<script setup lang="ts">
import { ref, watch, defineProps, nextTick, onMounted } from 'vue'
import type { PropType } from 'vue'
import type { ModelResult } from '@/stores/useModelStore'
import MarkdownPreview from './MarkdownPreview.vue'

import { showAlert } from '@/utils/useAlert'

import RobotSVG from '@/assets/img/robot.svg'
import UserSVG from '@/assets/img/user.svg'
import SendSVG from '@/assets/img/send.svg'
import CopySVG from '@/assets/img/copy.svg'

const props = defineProps({
  chatData: {
    type: Array as PropType<ModelResult[]>,
    required: true,
    default: () => [] as ModelResult[],
  },
  botAvatar: {
    type: String,
    default: RobotSVG,
  },
  userAvatar: {
    type: String,
    default: UserSVG,
  },
  botName: {
    type: String,
    default: '数字人',
  },
  userName: {
    type: String,
    default: '我',
  },
})

const chatListRef = ref<HTMLElement | null>(null)

watch(
  () => props.chatData,
  () => {
    nextTick(() => {
      if (chatListRef.value) {
        chatListRef.value.scrollTop = chatListRef.value.scrollHeight
      }
    })
  },
  { deep: true },
)
onMounted(() => {
  nextTick(() => {
    if (chatListRef.value) {
      chatListRef.value.scrollTop = chatListRef.value.scrollHeight
    }
  })
})

const copyToClipboard = (text: string, message: string) => {
  navigator.clipboard
    .writeText(text)
    .then(() => {
      showAlert(`${message}已复制到剪贴板`, 'info', 20000)
    })
    .catch((err) => {
      showAlert(`复制失败:${err}`, 'error', 20000)
    })
}
</script>

<template>
  <div
    ref="chatListRef"
    class="chat-preview w-full p-4 bg-gray-100 rounded-lg mx-auto"
    style="height: -webkit-fill-available; overflow: auto; scroll-behavior: smooth"
  >
    <!-- 滚动容器 -->
    <div class="space-y-6">
      <!-- 循环聊天内容 -->
      <div v-for="(item, index) in chatData" :key="index" class="flex flex-col space-y-4">
        <!-- 用户消息 -->
        <div class="flex justify-end items-start space-x-3 relative group">
          <div class="relative">
            <div class="text-sm text-gray-500 mb-1 text-right">{{ userName }}</div>
            <div class="bg-[#333] text-white p-4 rounded-lg shadow-sm max-w-2xl">
              {{ item.input }}
            </div>
            <!-- 用户复制按钮 -->
            <img
              :src="CopySVG"
              alt="复制"
              class="absolute -bottom-8 right-0 w-5 h-5 cursor-pointer opacity-70 hover:opacity-100 z-10"
              @click="copyToClipboard(item.input, '用户消息')"
            />
          </div>
          <img :src="userAvatar" alt="User Avatar" class="w-8 h-8 rounded-full object-cover" />
        </div>

        <!-- AI 回复 -->
        <div class="flex items-start space-x-3">
          <img :src="botAvatar" alt="Bot Avatar" class="w-8 h-8 rounded-full object-cover" />
          <div class="relative">
            <div class="text-sm text-gray-500 mb-1">{{ botName }}</div>
            <div v-if="item.isProcessing" class="bg-white p-4 rounded-lg shadow-sm max-w-2xl">
              <div class="mt-2 flex space-x-1">
                <div
                  class="w-2 h-2 bg-gray-400 rounded-full animate-bounce"
                  style="animation-delay: 0s"
                ></div>
                <div
                  class="w-2 h-2 bg-gray-400 rounded-full animate-bounce"
                  style="animation-delay: 0.2s"
                ></div>
                <div
                  class="w-2 h-2 bg-gray-400 rounded-full animate-bounce"
                  style="animation-delay: 0.4s"
                ></div>
              </div>
            </div>
            <div v-else class="bg-white rounded-lg shadow-sm max-w-2xl prose">
              <MarkdownPreview :content="item.result" />
            </div>
            <!-- AI 复制按钮 -->
            <img
              :src="CopySVG"
              alt="复制"
              class="absolute -bottom-8 left-0 w-5 h-5 cursor-pointer opacity-70 hover:opacity-100 z-10"
              @click="copyToClipboard(item.result, 'AI 回复')"
            />
          </div>
        </div>
      </div>

      <div
        v-if="chatData.length === 0"
        class="flex flex-col items-center justify-center py-12 text-center"
      >
        <img :src="botAvatar" alt="Empty Chat" class="w-16 h-16 text-gray-300 mb-4" />
        <h3 class="text-lg font-medium text-gray-700">暂无聊天记录</h3>
        <div class="text-sm text-gray-500 mt-2">
          <span class="flex items-center justify-center">
            <span class="mr-1">🎙️</span>
            <span class="mx-1">按住说话 ·</span>
            <kbd class="ml-1 px-1 py-0.5 bg-gray-200 rounded text-xs">Shift+Q</kbd>
            <span class="mx-1">语音输入</span>
          </span>
        </div>
        <div class="text-sm text-gray-500 mt-2">
          <span class="flex items-center justify-center">
            <span class="mr-1">✏️</span>
            <span class="mx-1">输入文字后按</span>
            <kbd class="mx-1 px-1 py-0.5 bg-gray-200 rounded text-xs">Enter</kbd>
            <span class="mx-1">或</span>
            <div
              class="inline-flex items-center justify-center p-[0.3vw] rounded-full bg-[#8b5cf6]"
            >
              <img :src="SendSVG" class="w-[0.6vw] h-[0.6vw]" alt="" />
            </div>
            <div class="mx-1">开始对话</div>
          </span>
        </div>
      </div>
    </div>
  </div>
</template>

<style scoped>
.chat-preview {
  height: -webkit-fill-available;
  overflow: auto;
  scroll-behavior: smooth;
}
.prose {
  @apply max-w-none;
}
</style>
