<script setup lang="ts">
import { ref, computed, defineProps } from 'vue'

const props = defineProps({
  message: {
    type: String,
    required: true,
  },
  type: {
    type: String as () => 'success' | 'error' | 'info' | 'warning',
    default: 'info',
  },
  duration: {
    type: Number,
    default: 3000,
  },
  offset: {
    type: [String, Number],
    default: 0,
  },
  onClose: {
    type: Function,
    required: true,
  },
})

const iconMap = {
  success: '✅',
  error: '❌',
  info: 'ℹ️',
  warning: '⚠️',
}

const icon = computed(() => iconMap[props.type])

const typeClass = computed(() => `alert-${props.type}`)

const positionStyle = computed(() => ({
  top: props.offset
}))

const isVisible = ref(true)

setTimeout(() => {
  isVisible.value  = false
  props.onClose()
}, props.duration)
</script>

<template>
  <Teleport to="body">
    <transition name="fade">
      <div v-show="isVisible" class="alert-container" :class="typeClass" :style="positionStyle">
        <div class="alert-content">
          <span v-if="icon" class="alert-icon">{{ icon }}</span>
          <span class="alert-message">{{ message }}</span>
        </div>
      </div>
    </transition>
  </Teleport>
</template>

<style scoped>
.alert-container {
  position: fixed;
  left: 50%;
  transform: translateX(-50%);
  height: 5vh;
  padding: 0.5vw 1.5vw;
  border-radius: 0.5vw;
  color: #fff;
  font-size: 1vw;
  display: flex;
  align-items: center;
  z-index: 9999;
  box-shadow: 0 0.1vw 0.8vw rgba(0, 0, 0, 0.15);
  transition: all 0.3s ease, opacity 0.3s ease;
}

.alert-success {
  color: #67c23a;
  background: #f0f9eb;
}
.alert-error {
  color: #f56c6c;
  background: #fef0f0;
}
.alert-info {
  color: #909399;
  background: #f4f4f5;
}
.alert-warning {
  color: #e6a23c;
  background: #fdf6ec;
}

.alert-content {
  display: flex;
  align-items: center;
}

.alert-icon {
  margin-right: 0.2vw;
}

.fade-enter-active,
.fade-leave-active {
  transition: opacity 0.3s ease;
}
.fade-enter-from,
.fade-leave-to {
  opacity: 0;
}
</style>
