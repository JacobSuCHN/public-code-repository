<template>
  <div class="live2d-container">
    <canvas ref="live2dCanvas" class="live2d-canvas"></canvas>
  </div>
</template>

<script setup lang="ts">
import { ref, onMounted } from 'vue'
import { useLive2DStore } from '@/stores/useLive2DStore'

const live2dCanvas = ref<HTMLCanvasElement>()
const live2DStore = useLive2DStore()

onMounted(() => {
  if (live2dCanvas.value)  {
    live2DStore.initializeModel(live2dCanvas.value)
  }
})
</script>

<style scoped>
.live2d-container {
  display: flex;
  justify-content: center;
  align-items: center;
}
.live2d-canvas {
  width: 500px;
  height: 500px;
}
.action-btn {
  margin: 10px 5px;
  padding: 6px 12px;
  border-radius: 4px;
  border: none;
  background: #409eff;
  color: #fff;
  cursor: pointer;
}
</style>
