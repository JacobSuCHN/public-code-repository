<script setup lang="ts">
import LeftComponent from './component/LeftComponent.vue'
import RightComponent from './component/RightComponent.vue'
import MiddleComponent from './component/MiddleComponent.vue';
</script>

<template>
  <div class="flex justify-between h-screen w-full overflow-hidden bg-gray-50">
    <div class="w-[35vw] h-full flex flex-col">
      <LeftComponent class="flex-1 overflow-y-auto" />
    </div>

    <div class="w-[30vw] h-full flex items-center justify-center p-0">
      <MiddleComponent class="w-full h-full" />
    </div>

    <div class="w-[35vw] h-full flex flex-col">
      <RightComponent class="flex-1 overflow-y-auto" />
    </div>
  </div>
</template>

<style scoped>
</style>
