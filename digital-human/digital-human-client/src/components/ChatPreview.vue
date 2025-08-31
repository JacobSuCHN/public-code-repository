<script setup lang="ts">
import { ref, watch, defineProps, nextTick, onMounted } from 'vue'
import type { PropType } from 'vue'
import type { ModelResult } from '@/stores/useModelStore'
import MarkdownPreview from './MarkdownPreview.vue'
import RobotSVG from '@/assets/img/robot.svg'
import UserSVG from '@/assets/img/user.svg'

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
