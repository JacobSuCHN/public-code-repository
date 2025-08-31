<script setup lang="ts">
import { useModelStore } from '@/stores/useModelStore'
import { ref, computed } from 'vue'
import ExpandLeftSVG from '@/assets/img/expand-left.svg'
import ExpandRightSVG from '@/assets/img/expand-right.svg'
import AddSVG from '@/assets/img/add.svg'
const modelStore = useModelStore()

// 全局折叠状态
const isAllCollapsed = ref(false)

// 格式化时间
const formatDate = (date: Date | undefined | null) => {
  return !!date
    ? new Date(date).toLocaleTimeString([], {
        year: 'numeric',
        month: '2-digit',
        day: '2-digit',
        hour: '2-digit',
        minute: '2-digit',
        second: '2-digit',
      })
    : ''
}

// 截断文本
const truncateText = (text: string | undefined, maxLength = 40) => {
  return text && text.length > maxLength ? text.substring(0, maxLength) + '...' : text
}

// 切换全局折叠状态
const toggleAllCards = () => {
  isAllCollapsed.value = !isAllCollapsed.value
}

// 计算是否有历史记录
const hasSessions = computed(() => {
  return modelStore.getAllSessions.length > 0
})

const createChat = () => {
  modelStore.createNewChat()
}
</script>

<template>
  <div class="card-container">
    <template v-if="!hasSessions">
      <div class="empty-state">暂无历史记录</div>
    </template>

    <template v-else>
      <!-- 全局控制区域 -->
      <div class="global-controls">
        <button v-if="!isAllCollapsed" class="add-button" @click="createChat" title="新建对话">
          <img :src="AddSVG" class="w-[1.2vw] h-[1.2vw]" alt="新建" />
        </button>
        <button class="toggle-all-button" @click="toggleAllCards">
          <img
            :src="isAllCollapsed ? ExpandLeftSVG : ExpandRightSVG"
            :title="isAllCollapsed ? '展开' : '折叠'"
            alt="折叠"
            class="w-[1.2vw] h-[1.2vw]"
          />
        </button>
      </div>

      <template v-if="!isAllCollapsed">
        <div
          v-for="(session, index) in modelStore.getAllSessions"
          :key="index"
          :class="{
            card: true,
            highlighted: index === modelStore.currentSessionIndex,
          }"
          @click="modelStore.setCurrentSessionIndex(session.sessionId)"
        >
          <div class="card-content">
            <div class="card-header">
              <div class="card-title">
                {{ truncateText(session.input) }}
              </div>
            </div>
            <div class="card-time">{{ formatDate(session.latest) }}</div>
          </div>
        </div>
      </template>
    </template>
  </div>
</template>

<style scoped>
.card-container {
  display: flex;
  flex-direction: column;
  gap: 0.8vw;
  padding: 1vw;
  background-color: #f9fafb;
  height: 100%;
  overflow-y: auto;
  position: relative;
}

.card-container.collapse {
  width: 5vw;
}

.global-controls {
  display: flex;
  justify-content: space-between;
  margin-bottom: 0.5vw;
}

.add-button,
.toggle-all-button {
  display: flex;
  align-items: center;
  justify-content: center;
  background: linear-gradient(135deg, #6366f1, #4f46e5);
  border: none;
  border-radius: 0.5vw;
  padding: 0.3vw;
  font-size: 0.9vw;
  cursor: pointer;
  box-shadow: 0 0.2vw 0.5vw rgba(79, 70, 229, 0.2);
}

.add-button:hover,
.toggle-all-button:hover {
  background: linear-gradient(135deg, #4f46e5, #4338ca);
  transform: translateY(-0.1vw);
  box-shadow: 0 0.3vw 0.6vw rgba(79, 70, 229, 0.3);
}

.toggle-all-button:active,
.toggle-all-button:active {
  transform: translateY(0);
}

.card {
  background: linear-gradient(135deg, #f0f4ff, #e6e9ff);
  border-radius: 1vw;
  box-shadow: 0 0.5vw 1vw rgba(79, 70, 229, 0.12);
  cursor: pointer;
  padding: 1vw 1.2vw;
  position: relative;
  display: inline-flex;
  border: 0.1vw solid transparent;
}
.card.highlighted {
  border-color: #4f46e5;
}
.card:hover {
  box-shadow: 0 0.3vw 0.6vw rgba(79, 70, 229, 0.2);
}

.card-content {
  display: flex;
  flex-direction: column;
  width: 15vw;
}

.card-time {
  font-size: 0.85vw;
  color: #64748b;
}
.card-title {
  font-size: 0.95vw;
  color: #333;
  margin-bottom: 0.2vw;
}
.card-header {
  margin-bottom: 0.2vw;
  padding-bottom: 0.2vw;
  border-bottom: 0.1vw dashed #c7d2fe;
}

.collapse-icon .icon {
  width: 1.2vw;
  height: 1.2vw;
}

.status-generating {
  color: #f59e0b;
  font-weight: 500;
}

.status-success {
  color: #10b981;
  font-weight: 500;
}

.status-error {
  color: #ef4444;
  font-weight: 500;
}

.empty-state {
  text-align: center;
  color: #94a3b8;
  font-style: italic;
  padding: 2vw;
}
</style>
