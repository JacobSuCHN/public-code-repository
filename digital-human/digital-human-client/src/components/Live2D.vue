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
  if (live2dCanvas.value) {
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
  width: 30vw;
  height: 30vw;
  image-rendering: pixelated;
}
.action-btn {
  margin: 1vw 0.5vw;
  padding: 0.5vw 1vw;
  border-radius: 0.3vw;
  border: none;
  background: #409eff;
  color: #fff;
  cursor: pointer;
}
</style>
