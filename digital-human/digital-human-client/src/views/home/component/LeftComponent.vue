<script setup lang="ts">
import { computed } from 'vue'
import MarkdownPreview from '@/components/MarkdownPreview.vue'
import { useModelStore } from '@/stores/useModelStore'

const modelStore = useModelStore()

// 当前选中项的内容
const markdownContent = computed(() =>
  modelStore.getCurrentResult?.result  || '请从历史记录中选择一项'
)

// 格式化时间显示
const formatDate = (date: Date) => {
  return new Date(date).toLocaleTimeString([], {
    year: 'numeric',
    month: '2-digit',
    day: '2-digit',
    hour: '2-digit',
    minute: '2-digit',
    second: '2-digit'
  })
}

// 截断过长的文本
const truncateText = (text: string, maxLength = 40) => {
  return text.length  > maxLength
    ? text.substring(0,  maxLength) + '...'
    : text
}

// 处理行点击事件
const handleRowClick = (index: number) => {
  modelStore.setCurrentIndex(index)
}
</script>

<template>
<div class="markdown-container">
  <!-- 历史记录表格 -->
  <div class="history-table">
    <!-- 表头 -->
    <div class="table-header">
      <div class="table-cell input-cell">输入内容</div>
      <div class="table-cell time-cell">时间</div>
      <div class="table-cell status-cell">状态</div>
    </div>

    <!-- 表格内容 -->
    <div class="table-body">
      <div
        v-for="(item, index) in modelStore.callHistory"
        :key="index"
        class="table-row"
        :class="{ 'active': index === modelStore.currentIndex   }"
        @click="handleRowClick(index)"
      >
        <div class="table-cell input-cell">
          {{ truncateText(item.input)   }}
        </div>
        <div class="table-cell time-cell">
          {{ formatDate(item.timestamp)   }}
        </div>
        <div class="table-cell status-cell">
          <span :class="{
            'status-generating': item.result   === '生成中...',
            'status-success': item.result   !== '生成中...'
          }">
            {{ item.result   === '生成中...' ? '生成中' : '已完成' }}
          </span>
        </div>
      </div>

      <!-- 空状态提示 -->
      <div v-if="modelStore.callHistory.length   === 0" class="empty-state">
        <div class="table-cell full-row">暂无历史记录</div>
      </div>
    </div>
  </div>

  <!-- Markdown 预览区域 -->
  <div class="markdown-content">
    <div v-if="modelStore.callHistory.length   > 0" class="preview-header">
      预览结果 ({{ modelStore.currentIndex   + 1 }}/{{ modelStore.callHistory.length   }})
    </div>
    <MarkdownPreview :content="markdownContent" />
  </div>
</div>
</template>

<style scoped>
.markdown-container {
  display: flex;
  flex-direction: column;
  max-width: 960px;
  height: 80vh;
  background-color: transparent;
  overflow: hidden;
}

/* 历史记录表格样式 - 修改部分 */
.history-table {
  display: flex;
  flex-direction: column;
  background: linear-gradient(135deg, #f0f4ff, #e6e9ff);
  border-bottom: 1px solid #e2e8f0;
  /* 添加圆角 */
  border-radius: 16px;
  /* 添加上下左右边距 */
  margin: 16px;
  /* 添加阴影提升层次感 */
  box-shadow: 0 4px 12px rgba(79, 70, 229, 0.12);
  /* 添加溢出隐藏确保圆角生效 */
  overflow: hidden;
}

.table-header {
  display: flex;
  background: linear-gradient(135deg, #4f46e5, #6366f1);
  color: white;
  font-weight: 600;
  padding: 0.8rem 0;
  position: sticky;
  top: 0;
  z-index: 10;
  /* 确保表头也有圆角 */
  border-top-left-radius: 16px;
  border-top-right-radius: 16px;
}

.table-body {
  max-height: 250px;
  overflow-y: auto;
}

/* Markdown 预览区域 - 修改部分 */
.markdown-content {
  display: flex;
  flex-direction: column;
  flex: 1;
  height: -webkit-fill-available;
  background-color: #ffffff;
  /* 添加圆角 */
  border-radius: 16px;
  /* 添加上下左右边距 */
  margin: 0 16px 16px 16px;
  /* 添加阴影提升层次感 */
  box-shadow: 0 4px 16px rgba(0, 0, 0, 0.08);
  /* 添加溢出隐藏确保圆角生效 */
  overflow: hidden;
}

/* 其他原有样式保持不变 */
.table-row {
  display: flex;
  padding: 0.8rem 0;
  border-bottom: 1px solid #edf2f7;
  cursor: pointer;
  transition: all 0.2s ease;
}

.table-row:hover {
  background-color: #f1f5ff;
}

.table-row.active   {
  background-color: #e0e7ff;
  border-left: 4px solid #4f46e5;
}

.table-cell {
  padding: 0 1rem;
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
  min-width: 200px;
}

.status-cell {
  flex: 1;
  min-width: 80px;
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

.empty-state {
  display: flex;
  justify-content: center;
  padding: 1.5rem;
  color: #94a3b8;
  font-style: italic;
}

.preview-header {
  padding: 1rem;
  background: linear-gradient(135deg, #f1f5f9, #b2d3fc);
  color: #4f46e5;
  font-weight: 600;
  border-bottom: 1px solid #e2e8f0;
}

/* 滚动条样式优化 */
::-webkit-scrollbar {
  width: 8px;
  height: 8px;
}
::-webkit-scrollbar-thumb {
  background: linear-gradient(45deg, rgba(197, 210, 252, 0.8), rgba(212, 215, 253, 0.8));
  border-radius: 4px;
}
::-webkit-scrollbar-thumb:hover {
  background: linear-gradient(45deg, rgba(165, 180, 252, 0.9), rgba(183, 189, 250, 0.9));
}
</style>
