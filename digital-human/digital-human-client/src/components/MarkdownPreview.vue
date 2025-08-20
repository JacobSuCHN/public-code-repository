<script setup lang="ts">
import { MdPreview } from 'md-editor-v3'
import 'md-editor-v3/lib/preview.css'

// 定义组件 props
defineProps<{
  content: string
}>()
</script>

<template>
  <div class="result-content">
    <MdPreview style="background: transparent;" :modelValue="content" previewTheme="vuepress" codeTheme="kimbie" />
  </div>
</template>

<style scoped>
.result-content {
  padding: 1rem;
  font-size: 1rem;
  line-height: 1.6;
}
</style>
