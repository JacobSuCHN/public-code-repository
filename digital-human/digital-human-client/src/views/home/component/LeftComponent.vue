<script setup lang="ts">
import { ref, computed } from 'vue'
import MarkdownPreview from '@/components/MarkdownPreview.vue'
import { useModelStore } from '@/stores/useModelStore'

const modelStore = useModelStore()
const isCollapsed = ref(false) // 控制折叠状态

// 当前选中项的内容
const markdownContent = computed(
  () => modelStore.getCurrentResult?.result || '请从历史记录中选择一项',
)

// 格式化时间显示
const formatDate = (date: Date) => {
  return new Date(date).toLocaleTimeString([], {
    year: 'numeric',
    month: '2-digit',
    day: '2-digit',
    hour: '2-digit',
    minute: '2-digit',
    second: '2-digit',
  })
}

// 截断过长的文本
const truncateText = (text: string, maxLength = 40) => {
  return text.length > maxLength ? text.substring(0, maxLength) + '...' : text
}

// 处理行点击事件
const handleRowClick = (index: number) => {
  modelStore.setCurrentIndex(index)

  // 点击当前行时展开/折叠
  if (isCollapsed.value && index === modelStore.currentIndex) {
    isCollapsed.value = false
  }
}

// 切换折叠状态
const toggleCollapse = () => {
  isCollapsed.value = !isCollapsed.value
}
</script>

<template>
  <div class="markdown-container">
    <!-- 历史记录表格 -->
    <div class="history-table">
      <!-- 表头 - 移除折叠控制按钮 -->
      <div class="table-header">
        <div class="table-cell input-cell">输入内容</div>
        <div class="table-cell time-cell">时间</div>
        <div class="table-cell status-cell">状态</div>
        <div class="table-cell collapse-cell"></div>
        <!-- 保留空单元格保持对齐 -->
      </div>

      <!-- 表格内容 -->
      <div class="table-body" :class="{ collapsed: isCollapsed }">
        <!-- 折叠状态只显示当前行 -->
        <template v-if="isCollapsed">
          <div
            v-if="modelStore.callHistory.length > 0"
            class="table-row active collapsed-row"
            @click="handleRowClick(modelStore.currentIndex)"
          >
            <div
              class="table-cell input-cell"
              :title="modelStore.callHistory[modelStore.currentIndex].input"
            >
              {{ truncateText(modelStore.callHistory[modelStore.currentIndex].input) }}
            </div>
            <div class="table-cell time-cell">
              {{ formatDate(modelStore.callHistory[modelStore.currentIndex].timestamp) }}
            </div>
            <div class="table-cell status-cell">
              <span
                :class="{
                  'status-generating': modelStore.callHistory[modelStore.currentIndex].isLoading,
                  'status-success':
                    !modelStore.callHistory[modelStore.currentIndex].isLoading &&
                    modelStore.callHistory[modelStore.currentIndex].success,
                  'status-error':
                    !modelStore.callHistory[modelStore.currentIndex].isLoading &&
                    !modelStore.callHistory[modelStore.currentIndex].success,
                }"
              >
                {{
                  modelStore.callHistory[modelStore.currentIndex].isLoading
                    ? '生成中'
                    : modelStore.callHistory[modelStore.currentIndex].success
                      ? '成功'
                      : '失败'
                }}
              </span>
            </div>
            <div class="table-cell collapse-cell"></div>
          </div>
        </template>

        <!-- 展开状态显示所有行 -->
        <template v-else>
          <div
            v-for="(item, index) in modelStore.callHistory"
            :key="index"
            class="table-row"
            :class="{ active: index === modelStore.currentIndex }"
            @click="handleRowClick(index)"
          >
            <div class="table-cell input-cell" :title="item.input">
              {{ truncateText(item.input) }}
            </div>
            <div class="table-cell time-cell">
              {{ formatDate(item.timestamp) }}
            </div>
            <div class="table-cell status-cell">
              <span
                :class="{
                  'status-generating': item.isLoading,
                  'status-success': !item.isLoading && item.success,
                  'status-error': !item.isLoading && !item.success,
                }"
              >
                {{ item.isLoading ? '生成中' : item.success ? '成功' : '失败' }}
              </span>
            </div>
            <div class="table-cell collapse-cell"></div>
          </div>
        </template>

        <!-- 空状态提示 -->
        <div v-if="modelStore.callHistory.length === 0" class="empty-state">
          <div class="table-cell full-row">暂无历史记录</div>
        </div>
      </div>

      <!-- 将折叠按钮移到表格底部 -->
      <div class="table-footer">
        <button class="collapse-btn" @click="toggleCollapse">
          <img v-if="isCollapsed" src="../../../assets/img/down.svg" alt="" />
          <img v-else src="../../../assets/img/up.svg" alt="" />
        </button>
      </div>
    </div>

    <!-- Markdown 预览区域 -->
    <div class="markdown-content">
      <div v-if="modelStore.callHistory.length > 0" class="preview-header">
        预览结果 ({{ modelStore.currentIndex + 1 }}/{{ modelStore.callHistory.length }})
      </div>
      <MarkdownPreview :content="markdownContent" />
    </div>
  </div>
</template>

<style scoped>
.markdown-container {
  display: flex;
  flex-direction: column;
  width: 100%;
  height: 80vh;
  background-color: transparent;
  overflow: hidden;
}

/* 历史记录表格样式 */
.history-table {
  display: flex;
  flex-direction: column;
  background: linear-gradient(135deg, #f0f4ff, #e6e9ff);
  border-radius: 1vw;
  margin: 1vw;
  box-shadow: 0 0.25vw 0.75vw rgba(79, 70, 229, 0.12);
  overflow: hidden;
}

.table-header {
  display: flex;
  background: linear-gradient(135deg, #4f46e5, #6366f1);
  color: white;
  font-weight: 600;
  padding: 0.8vw 0;
  position: sticky;
  top: 0;
  z-index: 10;
}

.table-body {
  height: 15vw;
  overflow-y: auto;
}

.table-body.collapsed {
  height: 3vw; /* 单行高度 */
}

/* 新增表格底部样式 */
.table-footer {
  display: flex;
  justify-content: center;
  background-color: linear-gradient(135deg, #f0f4ff, #e6e9ff);
  border-top: 0.1vw solid #c7d2fe;
}

.collapse-btn {
  background: transparent;
  opacity: 0.8;
  border: none;
  display: flex;
  align-items: center;
  cursor: pointer;
}

.collapse-btn img {
  width: 1.7vw;
  height: 1.7vw;
}

.collapse-btn:hover {
  opacity: 1;
  transform: translateY(-0.1vw);
}

.collapse-btn svg {
  margin-left: 0.25vw;
}

/* 折叠状态下的行样式 */
.collapsed-row {
  background-color: #e0e7ff !important;
  border-left: 0.25vw solid #4f46e5;
  display: flex;
  padding: 0.8vw 0;
  cursor: pointer;
  border-bottom: none;
}

.collapsed-row:hover {
  background-color: #d0d7ff !important;
}

/* Markdown 预览区域 */
.markdown-content {
  display: flex;
  flex-direction: column;
  flex: 1;
  height: -webkit-fill-available;
  background-color: #ffffff;
  border-radius: 1vw;
  margin: 0 1vw 1vw 1vw;
  box-shadow: 0 0.25vw 1vw rgba(0, 0, 0, 0.08);
  overflow: hidden;
}

/* 其他原有样式保持不变 */
.table-row {
  display: flex;
  padding: 0.8vw 0;
  border-bottom: 0.1vw solid #edf2f7;
  cursor: pointer;
  height: 3vw;
  align-items: center;
}

.table-row:hover {
  background-color: #f1f5ff;
}

.table-row.active {
  background-color: #e0e7ff;
  border-left: 0.25vw solid #4f46e5;
}

.table-cell {
  padding: 0 1vw;
  overflow: hidden;
  text-overflow: ellipsis;
  white-space: nowrap;
}

.input-cell {
  flex: 3;
  min-width: 0;
}

.time-cell {
  flex: 1;
  min-width: 12.5vw;
}

.status-cell {
  flex: 1;
  min-width: 5vw;
}

.full-row {
  flex: 1;
  text-align: center;
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
  display: flex;
  justify-content: center;
  color: #94a3b8;
  font-style: italic;
  align-items: center;
  height: 100%;
}

.preview-header {
  padding: 1vw;
  background: linear-gradient(135deg, #f1f5f9, #b2d3fc);
  color: #4f46e5;
  font-weight: 600;
  border-bottom: 0.1vw solid #e2e8f0;
  display: flex;
  justify-content: space-between;
  align-items: center;
}
</style>
