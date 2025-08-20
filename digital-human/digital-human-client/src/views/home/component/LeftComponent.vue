<script setup lang="ts">
import { computed } from 'vue'
import MarkdownPreview from '@/components/MarkdownPreview.vue'
import { useModelStore } from '@/stores/modelStore'
const modelStore = useModelStore()
const markdownContent = computed(() => modelStore.callHistory[0]?.result  || '')
</script>

<template>
  <MarkdownPreview :content="markdownContent" />
</template>

<style scoped>
.result-content {
  padding: 1rem;
  font-size: 1rem;
  line-height: 1.6;
}
</style>
