<script setup lang="ts">
import MarkdownPreview from '@/components/MarkdownPreview.vue'
import { useArticleStore } from '@/stores/useArticleStore'

const articleStore = useArticleStore()
articleStore.getArticle()
</script>

<template>
  <div class="markdown-container">
    <div class="markdown-content">
      <MarkdownPreview :content="articleStore.content" />
    </div>
  </div>
</template>

<style scoped>
.markdown-container {
  width: 100%;
  border-radius: 1vw;
  background-color: #f9fafb;
  box-shadow: 0 0.75vw 1.25vw rgba(0, 0, 0, 0.08);
  overflow: hidden;
}

.markdown-content {
  height: 100%;
  color: #333;
  line-height: 1.8;
  background-color: #f9fafb;
  overflow-y: auto;
  height: -webkit-fill-available;
}


</style>
