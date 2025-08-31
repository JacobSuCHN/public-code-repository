<script setup lang="ts">
import { useModelStore } from '@/stores/useModelStore'
import ChatPreview from '@/components/ChatPreview.vue'

const modelStore = useModelStore()
</script>

<template>
  <div class="markdown-container">
    <div class="markdown-content">
      <ChatPreview :chatData="modelStore.getCurrentSession" />
    </div>
  </div>
</template>

<style scoped>
.markdown-container {
  display: flex;
  flex-direction: column;
  width: 100%;
  height: 100%;
  overflow: hidden;
  background-color: #f9fafb;
  padding: 1vw;
}

.markdown-content {
  display: flex;
  flex-direction: column;
  flex: 1;
  height: -webkit-fill-available;
  background-color: #ffffff;
  border-radius: 1vw;
  box-shadow: 0 0.75vw 1.25vw rgba(0, 0, 0, 0.08);
  overflow: hidden;
}
</style>
