<script setup lang="ts">
import VoiceInput from '@/components/VoiceInput.vue'
import Live2D from '@/components/Live2D.vue';
</script>

<template>
  <div class="flex flex-col items-center justify-start h-full relative">
    <Live2D class="w-full "/>
    <VoiceInput class="w-full absolute bottom-2.5"/>
  </div>
</template>

<style scoped>
</style>
