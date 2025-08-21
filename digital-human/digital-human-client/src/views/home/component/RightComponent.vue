<script setup lang="ts">
import MarkdownPreview from '@/components/MarkdownPreview.vue'
import { useChartStore } from '@/stores/useChartStore'

const chartStore = useChartStore()
chartStore.fetchChartData()
</script>

<template>
  <div class="markdown-container">
    <div class="markdown-content">
      <MarkdownPreview :content="chartStore.content" />
    </div>
  </div>
</template>

<style scoped>
.markdown-container {
  max-width: 960px;
  border-radius: 15px;
  background-color: #f9fafb;
  box-shadow: 0 8px 20px rgba(0, 0, 0, 0.08);
  overflow: hidden;
}

.markdown-content {
  height: 100%;
  color: #333;
  line-height: 1.8;
  background-color: #f9fafb;
  transition: background-color 0.3s ease;
  overflow-y: auto;
  height: -webkit-fill-available;
}

/* 自定义滚动条样式 */
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
