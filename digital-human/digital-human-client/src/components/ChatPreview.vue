<script setup lang="ts">
import { ref, watch, defineProps, nextTick, onMounted } from 'vue'
import type { PropType } from 'vue'
import type { ModelResult } from '@/stores/useModelStore'
import MarkdownPreview from './MarkdownPreview.vue'
import RobotSVG from '@/assets/img/robot.svg'
import UserSVG from '@/assets/img/user.svg'
import SendSVG from '@/assets/img/send.svg'

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
    default: 'AI助手',
  },
  userName: {
    type: String,
    default: '用户',
  },
})

const chatListRef = ref<HTMLElement | null>(null)

watch(
  () => props.chatData,
  () => {
    // 确保 DOM 更新后再滚动
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
</script>

<template>
  <div ref="chatListRef" class="chat-preview w-full p-4 bg-gray-100 rounded-lg mx-auto">
    <!-- 滚动容器 -->
    <div class="space-y-6">
      <!-- 循环聊天内容 -->
      <div v-for="(item, index) in chatData" :key="index" class="flex flex-col space-y-4">
        <!-- 用户消息 -->
        <div class="flex justify-end items-start space-x-3">
          <div>
            <div class="text-sm text-gray-500 mb-1 text-right">{{ userName }}</div>
            <div class="bg-[#333] text-white p-4 rounded-lg shadow-sm max-w-2xl">
              {{ item.input }}
            </div>
          </div>
          <img :src="userAvatar" alt="User Avatar" class="w-8 h-8 rounded-full object-cover" />
        </div>

        <!-- AI 回复 -->
        <div class="flex items-start space-x-3">
          <img :src="botAvatar" alt="Bot Avatar" class="w-8 h-8 rounded-full object-cover" />
          <div>
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
          <span class="flex items-center">
            <span class="mr-1">🎙️</span>
            按住说话 ·
            <kbd class="ml-1 px-1 py-0.5 bg-gray-200 rounded text-xs">Shift+Q</kbd> 语音输入
          </span>
        </div>
        <div class="text-sm text-gray-500 mt-2">
          <span class="flex items-center">
            <span class="mr-1">✏️</span>
            输入文字后按 <kbd class="mx-1 px-1 py-0.5 bg-gray-200 rounded text-xs">Enter</kbd>
            <span class="mx-1">或</span>
            <div class="inline-flex items-center justify-center p-[0.3vw] rounded-full bg-[#8b5cf6]">
              <img :src="SendSVG" class="w-[0.6vw] h-[0.6vw]" alt="" />
            </div>
            <div class="ml-1">开始对话</div>
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
