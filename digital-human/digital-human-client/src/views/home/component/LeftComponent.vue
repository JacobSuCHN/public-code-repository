<script setup lang="ts">
import { computed } from 'vue'
import MarkdownPreview from '@/components/MarkdownPreview.vue'
import { useModelStore } from '@/stores/useModelStore'

const modelStore = useModelStore()
const markdownContent = computed(() => modelStore.callHistory[0]?.result || '')
</script>

<template>
  <div class="markdown-container">
    <header class="markdown-header">
      <h1>模型结果</h1>
    </header>

    <div class="markdown-content">
      <MarkdownPreview :content="markdownContent" />
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

.markdown-header {
  background: linear-gradient(135deg, #4f46e5, #6366f1);
  color: white;
  padding: 1rem;
  text-align: center;
  transition: background 0.3s ease;
}

.markdown-header h1 {
  font-size: 1.2rem;
  margin: 0;
  font-weight: 700;
}

.markdown-header p {
  margin-top: 0.5rem;
  font-size: 1rem;
  opacity: 0.9;
}

.markdown-content {
  padding: 2rem;
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
