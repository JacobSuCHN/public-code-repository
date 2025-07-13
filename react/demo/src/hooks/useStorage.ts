import { useSyncExternalStore } from "react"
// 导出一个名为useStorage的函数，接收两个参数：key和initialValue
export const useStorage = (key: string, initialValue: any) => {

  // 订阅者
  const subscribe = (callback: () => void) => {
    // 订阅浏览器API
    window.addEventListener('storage', callback)
    return () => {
      // 返回取消订阅
      window.removeEventListener('storage', callback)
    }
  }

  const getSnapshot = () => {
    // 从sessionStorage中获取key对应的值，如果存在则解析为JSON对象，否则返回initialValue
    return JSON.parse(sessionStorage.getItem(key)!) ?? initialValue
  }

  const res = useSyncExternalStore(subscribe, getSnapshot)
  const updateStorage = (value: any) => {
    sessionStorage.setItem(key, JSON.stringify(value))
    // 通知订阅者
    window.dispatchEvent(new StorageEvent('storage'))
  }
  return [res, updateStorage]
}
