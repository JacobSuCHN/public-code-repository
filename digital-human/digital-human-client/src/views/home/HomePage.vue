<script setup lang="ts">
import LeftComponent from './component/LeftComponent.vue'
import RightComponent from './component/RightComponent.vue'
import MiddleComponent from './component/MiddleComponent.vue';
</script>

<template>
  <div class="flex justify-between h-screen w-full overflow-hidden bg-gray-50">

    <div class="w-[30vw] h-full flex items-center justify-center p-[1vw]">
      <MiddleComponent class="w-full h-full" />
    </div>

    <div class="w-[70vw] py-[1vw] h-screen flex flex-row">
      <LeftComponent class="overflow-y-auto" />
      <RightComponent class="overflow-y-auto" />
    </div>
  </div>
</template>

<style scoped>
</style>
