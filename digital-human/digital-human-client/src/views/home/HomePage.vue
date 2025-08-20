<script setup lang="ts">
import LeftComponent from './component/LeftComponent.vue'
import RightComponent from './component/RightComponent.vue'
import MiddleComponent from './component/MiddleComponent.vue';
</script>

<template>
  <div class="flex h-screen w-full overflow-hidden bg-gray-50">
    <div class="w-1/3 h-full border-r border-gray-200 flex flex-col">
      <LeftComponent class="flex-1 overflow-y-auto" />
    </div>

    <div class="w-1/3 h-full flex items-center justify-center p-6">
      <MiddleComponent class="w-full h-full" />
    </div>

    <div class="w-1/3 h-full border-l border-gray-200 flex flex-col">
      <RightComponent class="flex-1 overflow-y-auto" />
    </div>
  </div>
</template>

<style scoped>
/* 自定义滚动条样式 */
::-webkit-scrollbar {
  width: 8px;
  height: 8px;
}
::-webkit-scrollbar-thumb {
  background: linear-gradient(45deg, rgba(197,210,252,0.8), rgba(212,215,253,0.8));
  border-radius: 4px;
}
::-webkit-scrollbar-thumb:hover {
  background: linear-gradient(45deg, rgba(165,180,252,0.9), rgba(183,189,250,0.9));
}
</style>
