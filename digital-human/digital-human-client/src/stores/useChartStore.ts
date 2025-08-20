// src/stores/chartStore.js
import { defineStore } from 'pinia'

export const useChartStore = defineStore('chart', {
  state: () => ({
    content: '',
  }),
  actions: {
    // 异步获取数据的方法
    async fetchChartData() {
      try {
        const res = await fetch('/api/chart', {
          method: 'GET',
          headers: { 'Content-Type': 'application/json' }
        })
        const data = await res.json()
        this.content = data?.content || '获取失败'
      } catch (err) {
        console.error("API 请求失败:", err)
      }
    }
  }
})
